/**
 * @file   requestsmanager.cpp
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Request Manager class definition.
 */

#include "requestsmanager.h"
#include "customexception.h"

RequestsManager::RequestsManager(EndpointRegister* ep_register,
                                 EndpointDelete* ep_delete,
                                 EndpointUpdate* ep_update,
                                 EndpointView* ep_view,
                                 EndpointGetDecrypData* ep_get_decryp_data,
                                 DBController* db_controller) :
    endpoint_register_(ep_register),
    endpoint_delete_(ep_delete),
    endpoint_update_(ep_update),
    endpoint_view_(ep_view),
    endpoint_get_decryp_data_(ep_get_decryp_data),
    db_controller_(db_controller)
{
    // Nothing to do here
}

RequestsManager::~RequestsManager(){
    // Close all the endpoints and delete them
    if(nullptr != endpoint_register_){
        endpoint_register_->close();
        delete endpoint_register_;
    }
    if(nullptr != endpoint_delete_){
        endpoint_delete_->close();
        delete endpoint_delete_;
    }
    if(nullptr != endpoint_update_){
        endpoint_update_->close();
        delete endpoint_update_;
    }
    if(nullptr != endpoint_view_){
        endpoint_view_->close();
        delete endpoint_view_;
    }
    if(nullptr != endpoint_get_decryp_data_){
        endpoint_get_decryp_data_->close();
        delete endpoint_get_decryp_data_;
    }
    // Also close and delete the database
    if(nullptr != db_controller_){
        db_controller_->close();
        delete db_controller_;
    }
}
void RequestsManager::onRegisterRequestEvent(const quint64 &requestId, const Content &content){
    bool res = false;
    QString error_message = "";
    try{
        // Check key length
        if(isKeyValid(content.getDecryptKey().size() << 3)){
            res = db_controller_->registerContent(content, &error_message);
            if(!res){
                throw CustomException(error_message);
            }
        } else {
            throw CustomException("Invalid key size");
        }
        endpoint_register_->respondRequest(requestId, error_message);
    }catch(const CustomException &e){
        if(nullptr != endpoint_register_){
            endpoint_register_->respondRequest(requestId, e.getMessage());
        }
    }
}

void RequestsManager::onDeleteRequestEvent(const quint64 &requestId, const qint64 &id){
    QString error_message = "";
    bool res = db_controller_->deleteContent(id, &error_message);
    if(nullptr != endpoint_delete_){
        endpoint_delete_->respondRequest(requestId, !res ? error_message : "");
    }
}

void RequestsManager::onUpdateRequestEvent(const quint64 &requestId, const Content &content){
    QString error_message = "";
    bool res = db_controller_->updateContent(content, &error_message);
    if(nullptr != endpoint_update_){
        endpoint_update_->respondRequest(requestId, !res ? error_message : "");
    }
}

void RequestsManager::onViewRequestEvent(const quint64& requestId, const qint64& id){
    QString error_message = "";
    Content content_data;
    bool res = db_controller_->getContent(id, &content_data, &error_message);
    if(nullptr != endpoint_view_){
        endpoint_view_->respondRequest(requestId, content_data, !res ? error_message : "");
    }
}

void RequestsManager::onGetDecryptDataRequestEvent(const quint64 &requestId, const qint64 &deviceId, const qint64 &contentId){
    try{
        QString error_message = "";

        if(!validateProtectionSystem(deviceId, contentId)){
            throw CustomException("Content's protection system and Device's protection system mismatch!");
        }

        // Obtain the encryption mode of the protection system that has been selected.
        ProtectionSystem protection_sys_data;
        bool res = db_controller_->getProtectionSystem(contentId, &protection_sys_data, &error_message);
        if(!res){
            throw CustomException(QString("Could not get protection system data from the database: %1").arg(error_message));
        }
        QString encryption_mode = protection_sys_data.getEncryptionMode();


        // Decrypt the data payload using the encryption mode and the symmetric key of that content.
        QAESEncryption::Mode aes_mode = getAesMode(encryption_mode);
        QAESEncryption::Aes key_length = getKeyLength(contentId);
        QByteArray decodedText = decryptPayload(contentId, aes_mode, key_length);

        // Respond the request with decoded data
        endpoint_get_decryp_data_->respondRequest(requestId, "", decodedText);

    } catch(const CustomException &e) {
        endpoint_get_decryp_data_->respondRequest(requestId, e.what(), "");
        qWarning() << e.what();
    }
}

QByteArray RequestsManager::decryptPayload(const qint64 contentId, QAESEncryption::Mode aes_mode, QAESEncryption::Aes key_length){
    Content content_data;
    QString error_message;
    bool res = db_controller_->getContent(contentId, &content_data, &error_message);
    if(!res){
        throw CustomException(QString("Could not get content data from the database: %1").arg(error_message));
    }
    QAESEncryption encryption(key_length, aes_mode);
    QByteArray key = content_data.getDecryptKey().toLocal8Bit();
    QByteArray decodedText = encryption.decode(QByteArray::fromHex(content_data.getPayloadData()), key);
    decodedText = encryption.removePadding(decodedText);
    return decodedText;
}

QAESEncryption::Mode RequestsManager::getAesMode(const QString& encryptionModeStr) {
    QAESEncryption::Mode aes_mode;
    if(encryptionModeStr == "AES + ECB") {
        aes_mode = QAESEncryption::ECB;
    } else if(encryptionModeStr == "AES + CBC") {
        aes_mode = QAESEncryption::CBC;
    } else {
        throw CustomException(QString("Unknown encryption mode %1").arg(encryptionModeStr).toStdString().c_str());
    }
    return aes_mode;
}

bool RequestsManager::validateProtectionSystem(const qint64 &deviceId, const qint64 &contentId){
    // Validate if the Content Protection System is the same as the device protection system. If it is
    // to proceed to the next step, if not, return an error.
    Content content_data;
    QString error_message;
    bool res = db_controller_->getContent(contentId, &content_data, &error_message);
    if(!res){
        throw CustomException(QString("Could not get content data from the database: %1").arg(error_message));
    }
    Device device_data;
    res = db_controller_->getDevice(deviceId, &device_data, &error_message);
    if(!res){
        throw CustomException(QString("Could not get device data from the database: %1").arg(error_message));
    }
    return content_data.getProtectionSystemId() == device_data.getProtectionSystemId();
}

QAESEncryption::Aes RequestsManager::getKeyLength(const qint64 &contentId){
    Content content_data;
    QString error_message;
    QAESEncryption::Aes key_length;
    bool res = db_controller_->getContent(contentId, &content_data, &error_message);
    if(!res){
        throw CustomException(QString("Could not get content data from the database: %1").arg(error_message));
    }
    switch(content_data.getDecryptKey().size() << 3) {
    case 128:
        key_length = QAESEncryption::AES_128;
        break;
    case 192:
        key_length = QAESEncryption::AES_192;
        break;
    case 256:
        key_length = QAESEncryption::AES_256;
        break;
    default:
        throw CustomException(QString("Unknown keylength %1").arg(content_data.getDecryptKey().size() << 3));
    }
    return key_length;
}

bool RequestsManager::isKeyValid(qint32 keySize) const {
    return keySize == 128 || keySize == 192 || keySize == 256;
}

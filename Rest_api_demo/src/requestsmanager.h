#ifndef REQUESTSMANAGER_H
#define REQUESTSMANAGER_H

/**
 * @file   requestsmanager.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Requests Manager class declaration.
 */

#include "endpoints/endpointregister.h"
#include "endpoints/endpointupdate.h"
#include "endpoints/endpointdelete.h"
#include "endpoints/endpointview.h"
#include "endpoints/endpointgetdecrypdata.h"
#include "dbcontroller.h"
#include "requestevents.h"
#include "qaescipher/qaesencryption.h"

/**
 * @brief The RequestsManager class implements the business logic
 * of the application.
 * It recieves the requests notified by the endpoints and uses
 * the Database Controller to handle the persistent data.
 */
class RequestsManager
{
public:

    /**
     * @brief Class contructor.
     * @param ep_register The endpoint for register requests to use.
     * @param ep_delete The endpoint for delete requests to use.
     * @param ep_update The endpoint for update requests to use.
     * @param ep_view The endpoint for view requests to use.
     * @param ep_get_decryp_data The endpoint for decrypted content requests to use.
     * @param db_controller The Databse Controller to use.
     */
    explicit RequestsManager(EndpointRegister* ep_register,
                    EndpointDelete* ep_delete,
                    EndpointUpdate* ep_update,
                    EndpointView* ep_view,
                    EndpointGetDecrypData* ep_get_decryp_data,
                    DBController* db_controller);

    /**
     * @brief Class destructor.
     */
    ~RequestsManager();

    /**
     * @brief Handles the RegisterRequestEvent message. This method tells the
     * Database Controller to write the data and then reponds the request through the proper endpoint.
     * @param requestId The request identifier to respond to.
     * @param content The Content to write on the Database.
     */
    void onRegisterRequestEvent(const quint64& requestId, const Content& content);

    /**
     * @brief Handles the DeleteRequestEvent message. This method tells the
     * Database Controller to remove the data and then reponds the request through the proper endpoint.
     * @param requestId The request identifier to respond to.
     * @param id The Content identifier to remove from the Database.
     */
    void onDeleteRequestEvent(const quint64& requestId, const qint64& id);

    /**
     * @brief Handles the UpdateRequestEvent message. This method tells the
     * Database Controller to update the data and then reponds the request through the proper endpoint.
     * @param requestId The request identifier to respond to.
     * @param content The new Content to write on the Database.
     */
    void onUpdateRequestEvent(const quint64& requestId, const Content& content);

    /**
     * @brief Handles the ViewRequestEvent message. This method tells the
     * Database Controller to get the data and then reponds the request through the proper endpoint.
     * @param requestId The request identifier to respond to.
     * @param content The Content to write on the Database
     */
    void onViewRequestEvent(const quint64& requestId, const qint64& id);

    /**
     * @brief Handles the GetDecryptDataRequestEvent message. This method checks if the Content Protection
     * System is the same as the Device protection system. If it is then decrypts the Content payload and
     * responds the request with this data.
     * @param requestId The request identifier to respond to.
     * @param deviceId The device identifier the content msut be played to.
     * @param contentId The Content identifier to decrypt.
     */
    void onGetDecryptDataRequestEvent(const quint64& requestId, const qint64& deviceId, const qint64& contentId);

private:

    friend class RequestManagerTest;

    /**
     * @brief Checks if the Device's protection system matches the Content protection system.
     * @param deviceId The device identifier to check.
     * @param contentId The content identifier to check.
     * @return true if protection system match.
     */
    bool validateProtectionSystem(const qint64 &deviceId, const qint64 &contentId);

    /**
     * @brief Decrypts the Content's payload.
     * @param contentId The Content id to decrypt.
     * @param aesMode The AES mode to use.
     * @param keyLength The Key length.
     * @return the plain content as a QByteArray.
     */
    QByteArray decryptPayload(const qint64 contentId, QAESEncryption::Mode aesMode, QAESEncryption::Aes keyLength);

    /**
     * @brief Returns the AES mode identifier for the given string.
     * @param encryptionModeStr The AES mdoe as string (i.e.: "AES + ECB")
     * @return the AES mode.
     */
    QAESEncryption::Mode getAesMode(const QString& encryptionModeStr);

    /**
     * @brief Gets the key length for AES.
     * @param contentId The content id to decrypt.
     * @return The key length.
     */
    QAESEncryption::Aes getKeyLength(const qint64 &contentId);

    /**
     * @brief Checks if a key size (in bits) is valid for the AES cypher.
     * @param keySize The key size in bits.
     * @return true is the key length is valid, false otherwise.
     */
    bool isKeyValid(qint32 keySize) const;

    EndpointRegister* endpoint_register_ = nullptr;             //!< The endpoint for register requests to use.
    EndpointDelete* endpoint_delete_ = nullptr;                 //!< The endpoint for delete requests to use.
    EndpointUpdate* endpoint_update_ = nullptr;                 //!< The endpoint for update requests to use.
    EndpointView* endpoint_view_ = nullptr;                     //!< The endpoint for view requests to use.
    EndpointGetDecrypData* endpoint_get_decryp_data_ = nullptr; //!< The endpoint for decrypted content requests to use.
    DBController* db_controller_ = nullptr;                     //!< The Databse Controller to use.
};

#endif // REQUESTSMANAGER_H

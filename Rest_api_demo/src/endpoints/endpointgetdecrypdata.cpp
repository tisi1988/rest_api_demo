/**
 * @file   endpointgetdecrypdata.cpp
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  EndpointGetDecrypData class definition.
 */

#include "endpointgetdecrypdata.h"
#include "../requestevents.h"
#include "../customexception.h"

EndpointGetDecrypData::EndpointGetDecrypData(QObject* controlProcess, quint16 ws_port) :
    ServerEndPoint(controlProcess, QString("http://0.0.0.0:%1/decryptdata").arg(ws_port).toStdString().c_str()) {
    webservice_.support(methods::GET, std::bind(&EndpointGetDecrypData::handleGet, this, std::placeholders::_1));
    webservice_.open().then([=] (pplx::task<void> previous_task) mutable {
        // Error handling on open
        if (previous_task._GetImpl()->_HasUserException()) {
            try {
                auto holder = previous_task._GetImpl()->_GetExceptionHolder(); // Probably should put in try
                // Need to make sure you try/catch here, as _RethrowUserException can throw
                holder->_RethrowUserException();
            } catch (std::exception& e) {
                qCritical() << e.what();
            }
        }
    });
}

void EndpointGetDecrypData::handleGet(http_request request) noexcept {
    QMutexLocker l(&request_mutex_);
    try{
        qInfo() << QString("Received Get Decrypted Data request from IP: %1")
                   .arg(QString::fromStdString(request.remote_address()));
        qint64 deviceId = -1, contentId = -1;
        parseGetDecryptDataRequestParams(uri::split_query(request.request_uri().query()), &deviceId, &contentId);
        // Store the requet for later response
        get_requests_.insert(request_id_, request);
        // Notify the application
        GetDecryptDataRequestEvent *m = new GetDecryptDataRequestEvent(request_id_, deviceId, contentId);
        QCoreApplication::postEvent(control_process_, m);
        request_id_++;
    } catch (const CustomException &e) {
        qWarning() << "Error parsing delete request's body: " << e.getMessage();
    }
}

void EndpointGetDecrypData::respondRequest(const quint64 requestId, const QString& errorMessage, const QByteArray& data) {
    try {
        QMutexLocker l(&request_mutex_);
        // Get the request to respond to from the map where is stored
        QMap<quint64, http_request>::iterator it = get_requests_.find(requestId);
        if(it != put_requests_.end()) {
            http_request request = it.value();
            // Create the response with the JSON data
            json::value response = buildResponseJsonData(errorMessage, data);
            quint16 result_code = status_codes::OK;
            if(!errorMessage.isEmpty()){
                result_code = status_codes::BadRequest;
            }
            qInfo() << QString("Outgoing Json data for Get Decrypted Data %1 to %2")
                       .arg(QString::fromStdString(response.serialize()))
                       .arg(QString::fromStdString(request.remote_address()));
            request.reply(result_code, response);
            put_requests_.remove(requestId);
        } else {
            throw CustomException("There given register request id does not exist");
        }
    } catch(const CustomException& e) {
        qCritical() << e.getMessage();
    }
}

void EndpointGetDecrypData::parseGetDecryptDataRequestParams(const map<string, string> params, qint64* deviceId, qint64* contentId) const {
    map<string, string>::const_iterator it;
    qint64 device_id = -1;
    qint64 content_id = -1;
    if(params.size() == 2) {
        it = params.find("device_id");
        if(it != params.end()) {
            device_id = QString::fromStdString(it->second).toInt();
        } else {
            throw CustomException("Parameter device_id not found");
        }
        it = params.find("content_id");
        if(it != params.end()) {
            content_id = QString::fromStdString(it->second).toInt();
        } else {
            throw CustomException("Parameter content_id not found");
        }
        *deviceId = device_id;
        *contentId = content_id;
    } else {
        throw CustomException("Invalid request param amount");
    }
}

json::value EndpointGetDecrypData::buildResponseJsonData(const QString& errorMessage, const QByteArray& data) const {
    try {
        json::value json_data;
        json_data["error"] = json::value::string(errorMessage.toStdString().c_str());
        json_data["data"] = json::value::string(data.toStdString().c_str());
        return json_data;
    } catch (std::exception &e) {
        throw CustomException(e.what());
    }
}

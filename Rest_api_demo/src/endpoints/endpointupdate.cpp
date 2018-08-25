/**
 * @file   endpointupdate.cpp
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  EndpointUpdate class definition.
 */

#include "endpointupdate.h"
#include "../requestevents.h"
#include "../customexception.h"

EndpointUpdate::EndpointUpdate(QObject* controlProcess, quint16 ws_port) :
    ServerEndPoint(controlProcess, QString("http://0.0.0.0:%1/update").arg(ws_port).toStdString().c_str()) {
    webservice_.support(methods::PUT, std::bind(&EndpointUpdate::handlePut, this, std::placeholders::_1));
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

void EndpointUpdate::handlePut(http_request request) noexcept {
    QMutexLocker l(&request_mutex_);
    try {
        qInfo() << QString("Received Update request from IP: %1")
                   .arg(QString::fromStdString(request.remote_address()));
        QString content_type = QString::fromStdString(request.headers().content_type());
        if(content_type != "application/json") {
            throw CustomException(QString("Invalid content type %1").arg(content_type));
        }
        Content content_to_update = parseUpdateRequestBody(request.extract_json().get());
        // Store the requet for later response
        put_requests_.insert(request_id_, request);
        // Notify the application
        UpdateRequestEvent *m = new UpdateRequestEvent(request_id_, content_to_update);
        QCoreApplication::postEvent(control_process_, m);
        request_id_++;
    } catch (const CustomException &e) {
        qWarning() << "Error parsing update request's body: " << e.getMessage();
    }
}

void EndpointUpdate::respondRequest(const quint64 requestId, const QString& errorMessage) {
    try {
        QMutexLocker l(&request_mutex_);
        // Get the request to respond to from the map where is stored
        QMap<quint64, http_request>::iterator it = put_requests_.find(requestId);
        if(it != put_requests_.end()) {
            http_request request = it.value();
            // Create the response with the JSON data
            json::value response;
            response["error"] = json::value::string(errorMessage.toStdString().c_str());
            quint16 result_code = status_codes::OK;
            if(!errorMessage.isEmpty()){
                result_code = status_codes::BadRequest;
            }
            qInfo() << QString("Outgoing Json data for Update %1 to %2")
                       .arg(QString::fromStdString(response.serialize()))
                       .arg(QString::fromStdString(request.remote_address()));
            request.reply(result_code, response);
            put_requests_.remove(requestId);
        } else {
            throw CustomException("There given update request id does not exist");
        }
    } catch(const CustomException& e) {
        qCritical() << e.getMessage();
    }
}

Content EndpointUpdate::parseUpdateRequestBody(const json::value& json_data) const {
    try {
        qint64 content_id = json_data.at(U("id")).as_number().to_int64();
        qint8 protection_system_id = json_data.at(U("protection_system_id")).as_integer();
        QString key = QString::fromStdString(json_data.at(U("key")).as_string());
        QByteArray payload_data = QByteArray::fromStdString(json_data.at(U("payload")).as_string());
        return Content(content_id, protection_system_id, key, payload_data);
    } catch (std::exception &e) {
        throw CustomException(e.what());
    }
}

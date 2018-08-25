/**
 * @file   endpointdelete.cpp
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  EndpointDelete class definition.
 */

#include "endpointdelete.h"
#include "../requestevents.h"
#include "../customexception.h"

EndpointDelete::EndpointDelete(QObject* controlProcess, quint16 ws_port) :
    ServerEndPoint(controlProcess, QString("http://0.0.0.0:%1/delete").arg(ws_port).toStdString().c_str()) {
    webservice_.support(methods::DEL, std::bind(&EndpointDelete::handleDelete, this, std::placeholders::_1));
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

void EndpointDelete::handleDelete(http_request request) noexcept {
    QMutexLocker l(&request_mutex_);
    try {
        qInfo() << QString("Received Delete request from IP: %1")
                   .arg(QString::fromStdString(request.remote_address()));
        qint64 content_id = parseDeleteRequestParams(uri::split_query(request.request_uri().query()));
        // Store the requet for later response
        delete_requests_.insert(request_id_, request);
        // Notify the application
        DeleteRequestEvent *m = new DeleteRequestEvent(request_id_, content_id);
        QCoreApplication::postEvent(control_process_, m);
        request_id_++;
    } catch (const CustomException &e) {
        qWarning() << "Error parsing delete request's body: " << e.what();
    }
}

void EndpointDelete::respondRequest(const quint64 requestId, const QString& errorMessage) {
    try {
        QMutexLocker l(&request_mutex_);
        // Get the request to respond to from the map where is stored
        QMap<quint64, http_request>::iterator it = delete_requests_.find(requestId);
        if(it != delete_requests_.end()) {
            http_request request = it.value();
            // Create the response with the JSON data
            json::value response;
            response["error"] = json::value::string(errorMessage.toStdString().c_str());
            quint16 result_code = status_codes::OK;
            if(!errorMessage.isEmpty()){
                result_code = status_codes::BadRequest;
            }
            qInfo() << QString("Outgoing Json data for Delete request %1 to %2")
                       .arg(QString::fromStdString(response.serialize()))
                       .arg(QString::fromStdString(request.remote_address()));
            request.reply(result_code, response);
            delete_requests_.remove(requestId);
        } else {
            throw CustomException("There given Delete request id does not exist");
        }
    } catch(const CustomException& e) {
        qCritical() << e.getMessage();
    }
}

qint64 EndpointDelete::parseDeleteRequestParams(const map<string, string> params) const {
    map<string, string>::const_iterator it;
    qint64 result_id = -1;
    if(params.size() == 1) {
        it = params.find("id");
        if(it != params.end()) {
            result_id = QString::fromStdString(it->second).toInt();
        } else {
            throw CustomException("Parameter device_id not found");
        }
    } else {
        throw CustomException("Invalid request param amount");
    }
    return result_id;
}

#include "endpointview.h"
#include "../requestevents.h"
#include "../customexception.h"

EndpointView::EndpointView(QObject* controlProcess, quint16 ws_port) :
    ServerEndPoint(controlProcess, QString("http://0.0.0.0:%1/view").arg(ws_port).toStdString().c_str()) {
    webservice_.support(methods::GET, std::bind(&EndpointView::handleGet, this, std::placeholders::_1));
    webservice_.open().then([=] (pplx::task<void> previous_task) mutable {
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

void EndpointView::handleGet(http_request request) noexcept {
    QMutexLocker l(&request_mutex_);
    try {
        qInfo() << QString("Received View request from IP: %1")
                   .arg(QString::fromStdString(request.remote_address()));
        qint64 content_id = parseViewRequestParams(uri::split_query(request.request_uri().query()));
        get_requests_.insert(request_counter_, request);
        ViewRequestEvent *m = new ViewRequestEvent(request_counter_, content_id);
        QCoreApplication::postEvent(control_process_, m);
        request_counter_++;
    } catch (const CustomException &e) {
        qWarning() << "Error parsing update request's body: " << e.getMessage();
    }
}

void EndpointView::respondRequest(const quint64 requestId, const Content& contentData, const QString& errorMessage) {
    try {
        QMutexLocker l(&request_mutex_);
        QMap<quint64, http_request>::iterator it = get_requests_.find(requestId);
        if(it != get_requests_.end()) {
            http_request request = it.value();
            json::value response;
            quint16 result_code = status_codes::OK;
            if(!errorMessage.isEmpty()){
                result_code = status_codes::BadRequest;
                response["error"] = json::value::string(errorMessage.toStdString().c_str());
            } else {
                response = buildResponseJsonData(contentData);
            }
            qInfo() << QString("Outgoing Json data for Update %1 to %2")
                       .arg(QString::fromStdString(response.serialize()))
                       .arg(QString::fromStdString(request.remote_address()));
            request.reply(result_code, response);
            get_requests_.remove(requestId);
        } else {
            throw "There given update request id does not exist";
        }
    } catch(const CustomException& e) {
        qCritical() << e.getMessage();
    }
}

qint64 EndpointView::parseViewRequestParams(const map<string, string> params) const {
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

json::value EndpointView::buildResponseJsonData(const Content& contentData) const {
    try {
        json::value json_data;
        json_data["id"] = json::value::number(static_cast<int64_t>(contentData.getId()));
        json_data["protection_system_id"] = json::value::number(contentData.getProtectionSystemId());
        json_data["key"] = json::value::string(contentData.getDecryptKey().toStdString().c_str());
        json_data["payload"] = json::value::string(contentData.getPayloadData().toStdString().c_str());
        return json_data;
    } catch (std::exception &e) {
        throw CustomException(e.what());
    }
}

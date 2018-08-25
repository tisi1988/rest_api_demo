#ifndef SERVERENDPOINT_H
#define SERVERENDPOINT_H

/**
 * @file   serverendpoint.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  Server endpoint class declaration.
 */

#include <QtCore>
#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"
#include "cpprest/filestream.h"
#include "cpprest/containerstream.h"
#include "cpprest/producerconsumerstream.h"

using namespace std;
using namespace web;
using namespace web::json;
using namespace web::http::client;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

/**
 * @brief The ServerEndPoint class implements an server endpoint using the
 * Casablanca library(See https://github.com/Microsoft/cpprestsdk for more
 * details). This library provides a C++ full REST SDK and also allows to
 * implement both client and server features.
 *
 * When a new request is received the endpoint parses the data and sends it
 * to the application control process. The message class includes the http
 * request identifier as a member for later response when the controller
 * has the data to send it back.
 *
 * This endpoint is opened when instantiated and holds a queue with all the
 * request received for each type (GET, PUT, ...). This queue is used to keep
 * the requests on memory until the response data is ready.
 */
class ServerEndPoint {
public:

    /**
     * @brief Class constructor. This constructor does not open any end point, therefore
     * this endpoint can be used only for client behaviour.
     * @param controllerProcess The controller process who created this end point.
     */
    explicit ServerEndPoint(QObject* controlProcess) : control_process_(controlProcess) {
        // Nothing to do
    }

    /**
     * @brief Class constructor.
     * @param controllerProcess The controller process who created this end point.
     * @param url The url to open.
     */
    ServerEndPoint(QObject *controlProcess, const QString& url) : control_process_(controlProcess) {
        http_listener_config cfg;
        cfg.set_timeout(std::chrono::seconds(5));
        webservice_ = http_listener(U(url.toStdString().c_str()), cfg);
    }

    /**
     * @brief Class destructor.
     */
    virtual ~ServerEndPoint() {
        webservice_.close().wait();
    }

    /**
     * @brief Clsoes the endpoint.
     */
    void close() {
        webservice_.close().wait();
    }

protected:

    /**
     * @brief Method to handle an error.
     * @param t The task which raised the error.
     */
    void handle_error(pplx::task<void>& t);

    http_listener webservice_;      //!< This is the listener which implements the webservice.

    quint64 request_id_ = 0;   //!< The counter used to assign the id the every request received.

    QMap<quint64, http_request> get_requests_;     //!< Queue used to hold the GET requests.
    QMap<quint64, http_request> delete_requests_;  //!< Queue used to hold the DEL requests.
    QMap<quint64, http_request> put_requests_;     //!< Queue used to hold the PUT requests.

    QMutex request_mutex_;  //!< Mutex used to make Casablanca's callbacks thread-safe.

    QObject* control_process_ = nullptr;  //!< The control process
};

#endif // SERVERENDPOINT_H

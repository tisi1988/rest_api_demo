#ifndef ENDPOINTDELETE_H
#define ENDPOINTDELETE_H

/**
 * @file   endpointdelete.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the EndpointDelete class.
 * The API of this endpoint is:
 *  - URL: /delete
 *  - PARAMS:
 *      + 'id' as number
 *  - BODY: (empty)
 *
 * The reponse content is:
 * - CODE:
 *      + 200 for OK
 *      + 400 for ERROR
 * - BODY:
 *      + Error message.
 */

#include "serverendpoint.h"

/**
 * @brief The EndpointDelete class implements the endpoint
 * in charge of receiving, and respond requests for Content deletion.
 */
class EndpointDelete : public ServerEndPoint {
public:

    /**
     * @brief Class constructor.
     * @param controlProcess The proces the endpoint must notify the incoming requests to.
     * @param ws_port The port where the endpoint must listen for incoming requests.
     */
    explicit EndpointDelete(QObject* controlProcess, quint16 ws_port);

    /**
     * @brief Responds to a previously received request with the given data.
     * @param requestId The request id to respond to.
     * @param errorMessage The error message to send.
     */
    void respondRequest(const quint64 requestId, const QString& errorMessage);

private:

    /**
     * @brief This method handles a new incoming request, parses the parameters and
     * notifies the control proces the request.
     * @param request the received request.
     */
    void handleDelete(http_request request) noexcept;

    /**
     * @brief Parses the Content identifier to remove from the database from the
     * incoming request.
     * @param params The parameters received on the incoming request.
     * @return the Content identifier to delete.
     */
    qint64 parseDeleteRequestParams(const map<string, string> params) const;
};

#endif // ENDPOINTDELETE_H

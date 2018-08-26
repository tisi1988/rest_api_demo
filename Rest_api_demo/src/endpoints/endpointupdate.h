#ifndef ENDPOINTUPDATE_H
#define ENDPOINTUPDATE_H

/**
 * @file   endpointupdate.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the EndpointUpdate class.
 * The API of this endpoint is:
 *  - URL: /update
 *  - PARAMS: (empty)
 *  - BODY:
 *      + 'id' as number.
 *      + 'protection_system_id' as number.
 *      + 'key' as string.
 *      + 'payload' as string.
 *
 * The reponse content is:
 * - CODE:
 *   + 200 for OK
 *   + 400 for ERROR
 * - BODY:
 *   + Error message.
 */

#include "serverendpoint.h"
#include "../datamodel/content.h"

/**
 * @brief The EndpointUpdate class implements the endpoint
 * in charge of receiving, and respond requests for Content data
 * updating.
 */
class EndpointUpdate : public ServerEndPoint {
public:

    /**
     * @brief Class constructor.
     * @param controlProcess The proces the endpoint must notify the incoming requests to.
     * @param ws_port The port where the endpoint must listen for incoming requests.
     */
    EndpointUpdate(QObject* controlProcess, quint16 ws_port);

    /**
     * @brief Responds to a previously received request with the given data.
     * @param requestId The request id to respond to.
     * @param errorMessage The error message to send.
     */
    void respondRequest(const quint64 requestId, const QString& errorMessage);

private:

    friend class EndpointUpdateTest;

    /**
     * @brief This method handles a new incoming request, parses the parameters and
     * notifies the control proces the request.
     * @param request the received request.
     */
    void handlePut(http_request request) noexcept;

    /**
     * @brief Parses the Content data to update from the request body as JSON data.
     * @param json_data The request body's JSON data.
     * @return The parsed data as a Content instance.
     */
    Content parseUpdateRequestBody(const json::value& json_data) const ;
};

#endif // ENDPOINTUPDATE_H

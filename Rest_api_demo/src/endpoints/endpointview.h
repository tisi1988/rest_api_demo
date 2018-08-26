#ifndef ENDPOINTVIEW_H
#define ENDPOINTVIEW_H

/**
 * @file   endpointupdate.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the EndpointUpdate class.
 *  *  The API of this endpoint is:
 *  - URL: /register
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
 *      + 'id' as number.
 *      + 'protection_system_id' as number.
 *      + 'key' as string.
 *      + 'payload' as string.
 */

#include "serverendpoint.h"
#include "../datamodel/content.h"

/**
 * @brief The EndpointUpdate class implements the endpoint
 * in charge of receiving, and respond requests for Content data
 * viewing.
 */
class EndpointView : public ServerEndPoint {
public:

    /**
     * @brief Class constructor.
     * @param controlProcess The proces the endpoint must notify the incoming requests to.
     * @param ws_port The port where the endpoint must listen for incoming requests.
     */
    EndpointView(QObject* controlProcess, quint16 ws_port);

    /**
     * @brief Responds to a previously received request with the given data.
     * @param requestId The request id to respond to.
     * @param errorMessage The error message to send.
     */
    void respondRequest(const quint64 requestId, const Content& contentData, const QString& errorMessage);

private:

    friend class EndpointViewTest;

    /**
     * @brief This method handles a new incoming request, parses the parameters and
     * notifies the control proces the request.
     * @param request the received request.
     */
    void handleGet(http_request request) noexcept;

    /**
     * @brief Parses the Content identifier from the request.
     * @param params The request parameters list.
     * @return The id of the Content whose data must be returned.
     */
    qint64 parseViewRequestParams(const map<string, string> params) const;

    /**
     * @brief Build the JSON data of the response with the Content data given.
     * @param contentData The Content to serialize into JSON data.
     * @return the JSON data to use to respond the request
     */
    json::value buildResponseJsonData(const Content& contentData) const;
};

#endif // ENDPOINTVIEW_H

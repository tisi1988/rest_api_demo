#ifndef ENDPOINTGETDECRYPDATA_H
#define ENDPOINTGETDECRYPDATA_H

/**
 * @file   endpointgetdecryptdata.h
 * @author Rubén Sánchez Castellano
 * @date   August 24, 2018
 * @brief  The declaration the EndpointGetDecrypData class.
 */

#include "serverendpoint.h"

/**
 * @brief The EndpointGetDecrypData class implements the endpoint
 * in charge of receiving, and respond requests for Content data
 * decryption and retrieval.
 */
class EndpointGetDecrypData : public ServerEndPoint {
public:

    /**
     * @brief Class constructor.
     * @param controlProcess The proces the endpoint must notify the incoming requests to.
     * @param ws_port The port where the endpoint must listen for incoming requests.
     */
    explicit EndpointGetDecrypData(QObject* controlProcess, quint16 ws_port);

    /**
     * @brief Responds to a previously received request with the given data.
     * @param requestId The request id to respond to.
     * @param errorMessage The error message to send.
     * @param data The decrypted payload data from the Content requested.
     */
    void respondRequest(const quint64 requestId, const QString& errorMessage, const QByteArray& data);
private:

    /**
     * @brief This method handles a new incoming request, parses the parameters and
     * notifies the control proces the request.
     * @param request the received request.
     */
    void handleGet(http_request request) noexcept;

    /**
     * @brief Parses the parameters of a received request.
     * @param params The parameters received on the incoming request.
     * @param deviceId The parsed device identifier.
     * @param contentId The parsed content identifier.
     */
    void parseGetDecryptDataRequestParams(const map<string, string> params, qint64* deviceId, qint64 *contentId) const;
};

#endif // ENDPOINTGETDECRYPDATA_H

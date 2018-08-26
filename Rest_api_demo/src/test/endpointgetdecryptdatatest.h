#ifndef ENDPOINTDECRYPTDATATEST_H
#define ENDPOINTDECRYPTDATATEST_H

#include <gtest/gtest.h>
#include "../endpoints/endpointgetdecrypdata.h"

class EndpointDecryptDataTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    void accessParseGetDecryptDataRequestParams(EndpointGetDecrypData* endpoint, const map<string, string>& params, qint64* deviceId, qint64 *contentId){
        return endpoint->parseGetDecryptDataRequestParams(params, deviceId, contentId);
    }

    json::value accessBuildResponseJsonData(EndpointGetDecrypData* endpoint, const QString& errorMessage, const QByteArray& data) {
        return endpoint->buildResponseJsonData(errorMessage, data);
    }
};


#endif // ENDPOINTDECRYPTDATATEST_H

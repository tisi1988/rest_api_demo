#ifndef ENDPOINTVIEWDATATEST_H
#define ENDPOINTVIEWDATATEST_H

#include <gtest/gtest.h>
#include "../endpoints/endpointview.h"

class EndpointViewTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    qint64 accessParseGetDecryptDataRequestParams(EndpointView* endpoint, const map<string, string>& params){
        return endpoint->parseViewRequestParams(params);
    }

    json::value accessBuildResponseJsonData(EndpointView* endpoint, const Content& contentData) {
        return endpoint->buildResponseJsonData(contentData);
    }
};


#endif // ENDPOINTDECRYPTDATATEST_H

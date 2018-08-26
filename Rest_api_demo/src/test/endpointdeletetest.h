#ifndef ENDPOINTDELETETEST_H
#define ENDPOINTDELETETEST_H

#include <gtest/gtest.h>
#include "../endpoints/endpointdelete.h"

class EndpointDeleteTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    qint64 accessParseDeleteRequestParams(EndpointDelete* endpoint, const map<string, string>& params){
        return endpoint->parseDeleteRequestParams(params);
    }
};


#endif // ENDPOINTDELETETEST_H

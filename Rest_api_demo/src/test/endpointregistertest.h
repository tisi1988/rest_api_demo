#ifndef ENDPOINTREGISTERTEST_H
#define ENDPOINTREGISTERTEST_H

#include <gtest/gtest.h>
#include "../endpoints/endpointregister.h"

class EndpointRegisterTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Content accessParseRegisterRequestBody(EndpointRegister* endpoint, const json::value& json_data) {
        return endpoint->parseRegisterRequestBody(json_data);
    }
};


#endif // ENDPOINTREGISTERTEST_H

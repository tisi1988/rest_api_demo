#ifndef ENDPOINTUPDATETEST_H
#define ENDPOINTUPDATETEST_H

#include <gtest/gtest.h>
#include "../endpoints/endpointupdate.h"

class EndpointUpdateTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Content accessParseUpdateRequestBody(EndpointUpdate* endpoint, const json::value& json_data) {
        return endpoint->parseUpdateRequestBody(json_data);
    }
};


#endif // ENDPOINTREGISTERTEST_H

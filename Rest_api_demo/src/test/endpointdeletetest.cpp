#include "endpointdeletetest.h"
#include "../customexception.h"

TEST_F(EndpointDeleteTest, 0_request_ok) {

    EndpointDelete ep(nullptr, 8088);
    map<string, string> params;
    params.insert(pair<string, string>{"id", "1"});
    qint64 id = 0;
    ASSERT_NO_THROW(id = accessParseDeleteRequestParams(&ep, params));
    ASSERT_EQ(id, 1);
}

TEST_F(EndpointDeleteTest, 1_request_empty_params) {

    EndpointDelete ep(nullptr, 8088);
    map<string, string> params;
    qint64 id;
    EXPECT_THROW(id = accessParseDeleteRequestParams(&ep, params), CustomException);
    Q_UNUSED(id)
}

TEST_F(EndpointDeleteTest, 2_request_unexpected_params) {

    EndpointDelete ep(nullptr, 8088);
    map<string, string> params;
    params.insert(pair<string, string>{"unexpected", "param"});
    qint64 id;
    EXPECT_THROW(id = accessParseDeleteRequestParams(&ep, params), CustomException);
    Q_UNUSED(id)
}

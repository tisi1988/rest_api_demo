#include "endpointviewtest.h"
#include "../customexception.h"

TEST_F(EndpointViewTest, 0_request_ok) {

    EndpointView ep(nullptr, 8088);
    map<string, string> params;
    params.insert(pair<string, string>{"id", "1"});
    qint64 id;
    ASSERT_NO_THROW(id = accessParseGetDecryptDataRequestParams(&ep, params));
    ASSERT_EQ(id, 1);
}

TEST_F(EndpointViewTest, 1_request_empty_params) {

    EndpointView ep(nullptr, 8088);
    map<string, string> params;
    EXPECT_THROW(accessParseGetDecryptDataRequestParams(&ep, params), CustomException);
}

TEST_F(EndpointViewTest, 2_request_unexpected_params) {

    EndpointView ep(nullptr, 8088);
    map<string, string> params;
    params.insert(pair<string, string>{"unexpected", "param"});
    EXPECT_THROW(accessParseGetDecryptDataRequestParams(&ep, params), CustomException);
}

TEST_F(EndpointViewTest, 3_build_json_data) {

    EndpointView ep(nullptr, 8088);
    Content data(1, 2, "KEY", QByteArray(1, 'c'));
    json::value json_data = accessBuildResponseJsonData(&ep, data);
    try {
        ASSERT_EQ(json_data.at("id").as_integer(), data.getId());
        ASSERT_EQ(json_data.at("protection_system_id").as_integer(), data.getProtectionSystemId());
        ASSERT_STREQ(json_data.at("key").as_string().c_str(), "KEY");
        ASSERT_STREQ(json_data.at("payload").as_string().c_str(), "c");
    } catch (std::exception &e) {
        ASSERT_FALSE(true);
    }
}

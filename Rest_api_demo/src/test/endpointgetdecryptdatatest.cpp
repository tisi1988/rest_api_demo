#include "endpointgetdecryptdatatest.h"
#include "../customexception.h"

TEST_F(EndpointDecryptDataTest, 0_request_ok) {

    EndpointGetDecrypData ep(nullptr, 8088);
    map<string, string> params;
    params.insert(pair<string, string>{"device_id", "1"});
    params.insert(pair<string, string>{"content_id", "2"});
    qint64 deviceId, contentId;
    ASSERT_NO_THROW(accessParseGetDecryptDataRequestParams(&ep, params, &deviceId, &contentId));
    ASSERT_EQ(deviceId, 1);
    ASSERT_EQ(contentId, 2);
}

TEST_F(EndpointDecryptDataTest, 1_request_empty_params) {

    EndpointGetDecrypData ep(nullptr, 8088);
    map<string, string> params;
    qint64 deviceId, contentId;
    EXPECT_THROW(accessParseGetDecryptDataRequestParams(&ep, params, &deviceId, &contentId), CustomException);
}

TEST_F(EndpointDecryptDataTest, 2_request_unexpected_params) {

    EndpointGetDecrypData ep(nullptr, 8088);
    map<string, string> params;
    params.insert(pair<string, string>{"unexpected", "param"});
    qint64 deviceId, contentId;
    EXPECT_THROW(accessParseGetDecryptDataRequestParams(&ep, params, &deviceId, &contentId), CustomException);
}

TEST_F(EndpointDecryptDataTest, 3_build_json_data) {

    EndpointGetDecrypData ep(nullptr, 8088);
    QByteArray data;
    data.append('c');
    json::value json_data = accessBuildResponseJsonData(&ep, "NO ERROR", data);
    try {
        ASSERT_STREQ(json_data.at("error").as_string().c_str(), "NO ERROR");
        ASSERT_STREQ(json_data.at("data").as_string().c_str(), "c");
    } catch (std::exception &e) {
        ASSERT_FALSE(true);
    }
}

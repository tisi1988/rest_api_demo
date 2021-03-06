#include "endpointupdatetest.h"
#include "../customexception.h"

TEST_F(EndpointUpdateTest, 0_request_ok) {

    EndpointUpdate ep(nullptr, 8088);
    json::value json_data;
    json_data["id"] = json::value::number(1);
    json_data["protection_system_id"] = json::value::number(2);
    json_data["key"] = json::value::string("KEY");
    json_data["payload"] = json::value::string("PAYLOAD");
    Content content;
    ASSERT_NO_THROW(content = accessParseUpdateRequestBody(&ep, json_data));
    ASSERT_EQ(content.getId(), 1);
    ASSERT_EQ(content.getProtectionSystemId(), 2);
    ASSERT_STREQ(content.getDecryptKey().toStdString().c_str(), "KEY");
    ASSERT_STREQ(content.getPayloadData().toStdString().c_str(), "PAYLOAD");
}

TEST_F(EndpointUpdateTest, 1_request_missing_key) {

    EndpointUpdate ep(nullptr, 8088);
    json::value json_data;
    json_data["id"] = json::value::number(1);
    json_data["protection_system_id"] = json::value::number(2);
//    json_data["key"] = json::value::string("KEY");
    json_data["payload"] = json::value::string("PAYLOAD");
    Content content;
    EXPECT_THROW(content = accessParseUpdateRequestBody(&ep, json_data), CustomException);
}

TEST_F(EndpointUpdateTest, 0_unexpected_additional_key) {

    EndpointUpdate ep(nullptr, 8088);
    json::value json_data;
    json_data["id"] = json::value::number(1);
    json_data["protection_system_id"] = json::value::number(2);
    json_data["key"] = json::value::string("KEY");
    json_data["payload"] = json::value::string("PAYLOAD");
    json_data["unexpected"] = json::value::string("KEY");
    Content content;
    ASSERT_NO_THROW(content = accessParseUpdateRequestBody(&ep, json_data));
    ASSERT_EQ(content.getId(), 1);
    ASSERT_EQ(content.getProtectionSystemId(), 2);
    ASSERT_STREQ(content.getDecryptKey().toStdString().c_str(), "KEY");
    ASSERT_STREQ(content.getPayloadData().toStdString().c_str(), "PAYLOAD");
}

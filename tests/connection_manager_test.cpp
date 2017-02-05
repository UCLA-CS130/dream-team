/*#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/connection_manager.h"
#include "../src/parsed_config.h"
#include "mock_parsed_config.h"

using ::testing::AtLeast;

TEST(ConnectionManagerTest, ValidGetRequest) {
  const std::string valid_get_req = 
    "GET /random_res HTTP/1.1\r\nContent-Type: text/plain\r\nConnection: Keep-Alive\r\n\r\nMessage of the Body.";

  const std::string expected_method = "GET";
  const std::string expected_uri = "/random_res";
  const std::string expected_version = "HTTP/1.1";
  const std::string expected_header_key1 = "Content-Type";
  const std::string expected_header_value1 = "text/plain";
  const std::string expected_header_key2 = "Connection";
  const std::string expected_header_value2 = "Keep-Alive";
  const std::string expected_body = "Message of the Body.";

  MockParsedConfig parsed_config;
  EXPECT_CALL(parsed_config, getPortNumber())
    .Times(AtLeast(1))
    .WillOnce(Return(2020));

  ConnectionManager manager(&parsed_config);

  HttpRequest req = parse_message(valid_get_req);
  HttpRequestLine request_line = req.GetRequestLine();
  EXPECT_EQ(expected_method, request_line.GetMethod());
  EXPECT_EQ(expected_uri, request_line.GetUri());
  EXPECT_EQ(expected_version, request_line.GetProtocolVersion());
  
  std::vector<std::string> keys = req.GetAllHeaderKeys();
  EXPECT_EQ(2, keys.size());
  EXPECT_EQ(expected_header_key1, keys[0]);
  EXPECT_EQ(expected_header_value1, req.FindHeader(keys[0]).GetValue());
  EXPECT_EQ(expected_header_key2, keys[1]);
  EXPECT_EQ(expected_header_value2, req.FindHeader(keys[1]).GetValue());
  EXPECT_EQ(expected_body, req.GetBody());
}

TEST(ConnectionManagerTest, InvalidGetRequest) {
  const std::string bad_req = "asdfas";
  
  const std::string expected_resp =
    "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n";

  MockParsedConfig parsed_config;
  EXPECT_CALL(parsed_config, getPortNumber())
    .Times(AtLeast(1))
    .WillOnce(Return(2020));
  
  ConnectionManager manager(&parsed_config);
  HttpResponse resp = manager.ProcessBadRequest(bad_req);
  EXPECT_EQ(resp.Serialize(), expected_resp);
}
*/
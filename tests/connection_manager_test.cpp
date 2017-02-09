#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/connection_manager.h"
#include "mock_basic_server_config.h"

using ::testing::AtLeast;
using ::testing::Return;

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

  MockBasicServerConfig basic_server_config;
  ConnectionManager manager(&basic_server_config);
  
  HttpRequest req = parse_message(valid_get_req);
  HttpRequestLine request_line = req.GetRequestLine();
  EXPECT_EQ(expected_method, request_line.GetMethod());
  EXPECT_EQ(expected_uri, request_line.GetUri());
  EXPECT_EQ(expected_version, request_line.GetProtocolVersion());

  HttpResponse resp = manager.ProcessGetRequest(req);
  StatusLine status = resp.GetStatusLine();
  
  EXPECT_EQ(status.GetStatusCode(), 200);
  EXPECT_EQ(status.GetProtocolVersion(), expected_version);
}

TEST(ConnectionManagerTest, InvalidGetRequest) {
  unsigned bad_req = 400;
  
  const std::string expected_resp =
    "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n";

  MockBasicServerConfig basic_server_config;
  ConnectionManager manager(&basic_server_config);
  HttpResponse resp = manager.ProcessBadRequest(bad_req);
  EXPECT_EQ(resp.Serialize(), expected_resp);
}

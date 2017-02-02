#include "gtest/gtest.h"
#include "../src/http_request_line.h"

TEST(HttpRequestLineTest, LineSerialization) {
  const std::string method = "GET";
  const std::string uri = "/resource";
  const std::string protocol = "Http/1.1";
  const std::string req_line = 
    method + " " + uri + " " + protocol;
  
  HttpRequestLine line(method, uri, protocol);

  EXPECT_EQ(line.GetMethod(), method);
  EXPECT_EQ(line.GetUri(), uri);
  EXPECT_EQ(line.GetProtocolVersion(), protocol);
  EXPECT_EQ(line.Serialize(), req_line);
}

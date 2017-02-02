//
//  http_request_test.cpp
//  
//
//  Created by Brian Cho on 2/1/17.
//
//

#include "gtest/gtest.h"
#include "../src/http_request.h"

TEST(HttpRequestTest, RequestSerialization){
  const std::string method = "GET";
  const std::string uri = "/fakePath/index.php";
  const std::string version = "HTTP/1.1";
  const std::string expectedSerialize = "GET /fakePath/index.php HTTP/1.1";
  
  HttpRequestLine requestLine(method, uri, version);
  HttpRequest request(requestLine);
  
  EXPECT_EQ(request.getRequestLine().Serialize(), expectedSerialize);
  EXPECT_EQ(method, request.getRequestLine().getMethod());
  EXPECT_EQ(uri, request.getRequestLine().getUri());
  EXPECT_EQ(version, request.getRequestLine().getProtocolVersion());
}

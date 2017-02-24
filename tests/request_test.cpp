//
//  request_test.cpp
//  
//
//  Created by Brian Cho on 2/22/17.
//
//

#include "gtest/gtest.h"
#include "../src/request.h"

TEST(RequestTest, RequestGenericTest) {
  const std::string method = "GET";
  const std::string uri = "/fakePath/index.php";
  const std::string version = "HTTP/1.1";
  
  const std::string req_line = method + " " + uri + " " + version;

  std::vector<std::pair<std::string, std::string>> headers;
  const std::string header1_key = "Content-Type";
  const std::string header1_value = "plain";
  const std::string header2_key = "Content-Length";
  const std::string header2_value = "512";
  
  const std::string header1 = header1_key + HEADER_KEY_VALUE_DELIMITER + header1_value;
  const std::string header2 = header2_key + HEADER_KEY_VALUE_DELIMITER + header2_value;
  headers.push_back(make_pair(header1_key, header1_value));
  headers.push_back(make_pair(header2_key, header2_value));
  
  std::string headers_str = "";
  for(int i = 0; i < headers.size(); i++){
    headers_str += HEADER_DELIMITER;
    headers_str += headers[i].first + HEADER_KEY_VALUE_DELIMITER + headers[i].second;
  }
  
  const std::string body = "body";
  const std::string ser_req = req_line + headers_str + REQUEST_DELIMITER + body + REQUEST_DELIMITER;
  
  std::unique_ptr<Request> req = Request::Parse(ser_req);
  
  
  EXPECT_EQ(ser_req, req->raw_request());
  EXPECT_EQ(method, req->method());
  EXPECT_EQ(uri, req->uri());
  EXPECT_EQ(version, req->version());
  EXPECT_EQ(body, req->body());
  
}

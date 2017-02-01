#include "gtest/gtest.h"
#include "../src/http_response.h"

TEST(HttpResponseTest, ResponseSerialization) {
  const std::string protocol_version = "HTTP/1.1";
  const unsigned status_code = 200;
  const std::string status_message = "OK";

  const std::string status_line = protocol_version + " " + std::to_string(status_code) + " " + status_message;
  const std::string body = "this is my custom body";

  HttpHeader header("myKey", "myVal");
  StatusLine parsed_status_line(protocol_version, status_code, status_message);

  HttpResponse response(parsed_status_line);
  response.AddHeader(header);
  response.SetBody(body);
  
  HttpMessage raw_response(status_line);
  raw_response.AddHeader(header);
  raw_response.SetBody(body);
  
  EXPECT_EQ(response.Serialize(), raw_response.Serialize());
}

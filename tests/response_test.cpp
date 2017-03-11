#include "gtest/gtest.h"
#include "../src/response.h"

TEST(ResponseTest, ResponseSerialization) {
  std::string expectedResponse = "";
  const std::string version = "HTTP/1.1";
  const std::string status = "OK";
  const std::string statusCode = "200";
  Response::ResponseCode expectedResponseCode = Response::ResponseCode::OK;
  
  expectedResponse += version + " " + statusCode + " " + status;
  
  std::vector<std::pair<std::string, std::string>> headers;
  const std::string header1_key = "Content-Type";
  const std::string header1_value = "plain";
  const std::string header2_key = "Content-Length";
  const std::string header2_value = "512";
  
  const std::string header1 = header1_key + HEADER_KEY_VALUE_DELIMITER + header1_value;
  const std::string header2 = header2_key + HEADER_KEY_VALUE_DELIMITER + header2_value;
  headers.push_back(make_pair(header1_key, header1_value));
  headers.push_back(make_pair(header2_key, header2_value));
  
  const std::string body = "<html></html>";
  
  Response* resp = new Response();
  
  resp->SetStatus(expectedResponseCode);
  for(unsigned i = 0; i < headers.size(); i++) {
    expectedResponse += HEADER_DELIMITER;
    expectedResponse += headers[i].first + HEADER_KEY_VALUE_DELIMITER + headers[i].second;
    
    resp->AddHeader(headers[i].first, headers[i].second);
  }
  
  expectedResponse += RESPONSE_DELIMITER;
  expectedResponse += body;
  resp->SetBody(body);
     
  EXPECT_EQ(expectedResponse, resp->ToString());  
  delete resp;
}

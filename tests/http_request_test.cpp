#include "gtest/gtest.h"
#include "../src/http_request.h"

TEST(HttpRequestTest, RequestSerialization){
  const std::string method = "GET";
  const std::string uri = "/fakePath/index.php";
  const std::string version = "HTTP/1.1";

  const std::string req_line = method + " " + uri + " " + version;
  const std::string ser_req = req_line + "\r\n\r\n";

  HttpRequestLine requestLine(method, uri, version);
  HttpRequest request(requestLine);
  
  EXPECT_EQ(request.Serialize(), ser_req);
}

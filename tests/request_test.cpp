#include "gtest/gtest.h"
#include "../src/request.h"

TEST(RequestTest, RequestSerialization){
  const std::string method = "GET";
  const std::string uri = "/fakePath/index.php";
  const std::string version = "HTTP/1.1";

  const std::string req_line = method + " " + uri + " " + version;
  const std::string headers = "Content-Type: plain" + "\r\n" + "Content-Length: 512" + "\r\n\r\n";
  const std::string body = "body";
  const std::string ser_req = req_line + headers + body + "\r\n\r\n";

  std::unique_ptr<Request> req = Request.Parse(ser_req);
   EXPECT_EQ(ser_req, req->raw_request());
  
}

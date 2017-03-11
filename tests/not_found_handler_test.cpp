#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "../src/not_found_handler.h"
#include "../src/nginx-configparser/config_parser.h"

class FileNotFoundHandlerTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig config_;
  NotFoundHandler* file_not_found_handler_;

  bool CreateFileNotFoundHandlerTest(const std::string config_string) {
    std::stringstream config_stream(config_string);

    if (!parser_.Parse(&config_stream, &config_)) {
      return false;
    }

    file_not_found_handler_ = new NotFoundHandler();
    return true;
  }

  Request CreateFileNotFoundTestRequest() {
    const std::string method = "GET";
    const std::string uri = "/fake_path";
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
    for(unsigned i = 0; i < headers.size(); i++){
      headers_str += HEADER_DELIMITER;
      headers_str += headers[i].first + HEADER_KEY_VALUE_DELIMITER + headers[i].second;
    }
	  
    const std::string body = "";
    const std::string ser_req = req_line + headers_str + REQUEST_DELIMITER + body + REQUEST_DELIMITER;
	  
    return *Request::Parse(ser_req);
  }
};

TEST_F(FileNotFoundHandlerTest, BasicFileNotFoundHandlerTest) {
  bool did_parse = CreateFileNotFoundHandlerTest("port 2020;\npath /echo EchoHandler {}\npath / StaticHandler {\n\t root tests/test_file_dir/;\n}\ndefault NotFoundHandler {}\n");
  EXPECT_TRUE(did_parse);
  EXPECT_EQ(0, file_not_found_handler_->Init("/fake_path", config_));

  Request req = CreateFileNotFoundTestRequest();
  Response resp;
  EXPECT_EQ(0, file_not_found_handler_->HandleRequest(req, &resp));

  EXPECT_EQ(404, resp.GetStatus());

  std::string expectedResponse = "";
  const std::string version = "HTTP/1.1";
  const std::string status = "Not Found";
  const std::string statusCode = "404";

  expectedResponse += version + " " + statusCode + " " + status + "\r\n";

  const std::string headerContent = "Content-Type: text/plain" ;

  expectedResponse += headerContent;
  expectedResponse += RESPONSE_DELIMITER;

  EXPECT_EQ(expectedResponse, resp.ToString());
}

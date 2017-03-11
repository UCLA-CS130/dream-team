#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "../src/static_handler.h"
#include "../src/nginx-configparser/config_parser.h"

class StaticHandlerTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig config_;
  StaticHandler* static_file_handler;
  const std::string body = "<html>\n\n<head>\n  <title>A very simple webpage</title>\n  <basefont size=4>\n</head>\n\n<body>\n  Here is some content\n</body>\n\n</html>\n";

  bool CreateStaticHandlerTest(const std::string config_string) {
    std::stringstream config_stream(config_string);

    if (!parser_.Parse(&config_stream, &config_)) {
      return false;
    }

    static_file_handler = new StaticHandler();
    return true;
  }

  Request CreateStaticTestRequest() {
    const std::string method = "GET";
    const std::string uri = "/simple.html";
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
    for(unsigned int i = 0; i < headers.size(); i++){
      headers_str += HEADER_DELIMITER;
      headers_str += headers[i].first + HEADER_KEY_VALUE_DELIMITER + headers[i].second;
    }

    const std::string ser_req = req_line + headers_str + REQUEST_DELIMITER + body;

    return *Request::Parse(ser_req);
  }
};

TEST_F(StaticHandlerTest, BasicStaticHandlerTest) {
  bool did_parse = CreateStaticHandlerTest("port 2020;\npath / StaticFileHandler {\nroot tests/test_file_dir;\n}\npath /echo EchoHandler {}\ndefault NotFoundHandler {}\n");
  EXPECT_TRUE(did_parse);
  EXPECT_EQ(0, static_file_handler->Init("/", *(config_.statements_[1]->child_block_.get())));

  Request req = CreateStaticTestRequest();
  Response resp;
  EXPECT_EQ(0, static_file_handler->HandleRequest(req, &resp));

  EXPECT_EQ(body, resp.GetBody());
}

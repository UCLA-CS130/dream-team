#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "../src/basic_server_config.h"


class BasicServerConfigTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig out_config_; 
  BasicServerConfig* basic_server_config_;

  bool CreateBasicServerConfig(const std::string config_string) {
    std::stringstream config_stream(config_string);

    if (!parser_.Parse(&config_stream, &out_config_)) {
      return false;
    }

    basic_server_config_ = new BasicServerConfig(&out_config_);
    return true;
  }
};

TEST_F(BasicServerConfigTest, BasicConfigTest) {
  bool did_parse = CreateBasicServerConfig("port 2020;\npath /echo EchoHandler {}\npath / StaticHandler {\n\t root tests/test_file_dir/;\n\t}\n");
  
  EXPECT_TRUE(did_parse);
  EXPECT_TRUE(basic_server_config_->Init());
  EXPECT_EQ(2020, basic_server_config_->GetPortNumber());
}

TEST_F(BasicServerConfigTest, InvalidConfigTest) {
  bool did_parse = CreateBasicServerConfig("server 2020; }");
  
  EXPECT_FALSE(did_parse);
  if(did_parse)
    EXPECT_FALSE(basic_server_config_->Init());
}

#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "../src/basic_server_config.h"

class BasicServerConfigTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig out_config_; 
  BasicServerConfig* basic_server_config_;

  void CreateBasicServerConfig(const std::string config_string) {
    std::stringstream config_stream(config_string);
    parser_.Parse(&config_stream, &out_config_);
    basic_server_config_ = new BasicServerConfig(&out_config_);
  }
};

TEST_F(BasicServerConfigTest, BasicConfigTest) {
  CreateBasicServerConfig("server {\n\tlisten 2020;\n}\n");
  EXPECT_FALSE(basic_server_config_->Init()); // this is no more considered a complete config
  EXPECT_EQ(2020, basic_server_config_->GetPortNumber());
}

TEST_F(BasicServerConfigTest, InvalidConfigTest) {
  CreateBasicServerConfig("server 2020; }");
  EXPECT_FALSE(basic_server_config_->Init());
}

TEST_F(BasicServerConfigTest, MultilineConfigTest) { 
  CreateBasicServerConfig("server {\n\tlisten 2020;\n\techo /echo;\n\tlocation / {\n\t root tests/test_file_dir/;\n\t}\n}\n");
  EXPECT_TRUE(basic_server_config_->Init());
  EXPECT_EQ(2020, basic_server_config_->GetPortNumber());
  EXPECT_EQ("/echo", basic_server_config_->GetEchoPath());
  EXPECT_EQ("tests/test_file_dir/", basic_server_config_->MapUserToHostUrl("/"));
}
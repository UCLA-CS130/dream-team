#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "../src/parsed_config.h"

class ParsedConfigTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig out_config_; 
  ParsedConfig* parsed_config_;

  void CreateParsedConfig(const std::string config_string) {
    std::stringstream config_stream(config_string);
    parser_.Parse(&config_stream, &out_config_);
    parsed_config_ = new ParsedConfig(&out_config_);
  }
};


TEST_F(ParsedConfigTest, BasicConfigTest) {
  CreateParsedConfig("server {\n\tlisten 2020;\n}\n");
  // Dont know how to use GetStatementValue
  // get parsed_config_->GetStatementValue(&out_config_, "listen")[0]) returns '\0'
  EXPECT_EQ("2020", parsed_config_->GetStatementValue(&out_config_, "listen")[0]);
}

TEST_F(ParsedConfigTest, InvalidConfigTest) {
  CreateParsedConfig("server 2020; }");
  EXPECT_EQ(0, parsed_config_->GetStatementValue(&out_config_, "listen"));
}

TEST_F(ParsedConfigTest, MultipleLineConfigTest) {
  CreateParsedConfig("server {\n\tlisten 2020;\n\troot ../;\n}\n");
  EXPECT_EQ(2020, parsed_config_->GetStatementValue(&out_config_, "listen"));
  EXPECT_EQ("../", parsed_config_->GetStatementValue(&out_config_, "root"));
}

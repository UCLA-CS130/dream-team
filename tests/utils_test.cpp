#include <sstream>
#include <string>
#include "gtest/gtest.h"
#include "../src/utils.h"

// From Assignment 1

class UtilsGetPortTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig out_config_;

  int GetPortNumber(const std::string config_string) {
    std::stringstream config_stream(config_string);
    parser_.Parse(&config_stream, &out_config_);
    return NginxConfigGetPort(&out_config_);
  }
};


TEST_F(UtilsGetPortTest, BasicConfigTest) {
  EXPECT_EQ(2020, GetPortNumber("server {\n\tlisten 2020;\n}\n"));
}

TEST_F(UtilsGetPortTest, InvalidConfigTest) {
  EXPECT_EQ(-1, GetPortNumber("server 2020; }"));
}

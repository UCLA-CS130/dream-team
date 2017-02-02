#include "gtest/gtest.h"
#include "../src/utils.h"

// From Assignment 1

class UtilsTest : public ::testing::Test {
protected:
  NginxConfigParser parser_;
  NginxConfig config_;

  bool ParseString(const std::string config_string) {
    std::stringstream config_stream(config_string);
    return parser_.Parse(&config_stream, &config_);
  }
};


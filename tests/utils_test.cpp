#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include "gtest/gtest.h"
#include "../src/utils.h"

TEST(TokenizorTest, SimpleTokenize) {
  std::vector<std::string> tokens = {"hello", "bob", "how", "are", "you", "doing"};
  
  const std::string delim = "\r\n";
  std::string ser_version = "";  
  for (auto tok : tokens) {
    ser_version += delim + tok;
  }
  
  ser_version = boost::algorithm::trim_copy(ser_version);

  std::vector<std::string> ser_tokenized;
  tokenize(ser_version, ser_tokenized, delim);

  EXPECT_EQ(ser_tokenized.size(), tokens.size());
  for (unsigned i = 0; i < ser_tokenized.size(); i++) {
    EXPECT_EQ(ser_tokenized[i], tokens[i]);
  }
}

TEST(UriTest, SimpleUri) {
  const std::string uri = "/index.html";
  std::string uri_start = GetUriStart(uri);
  EXPECT_EQ(uri_start, "/index.html");
}

TEST(UriTest, MultipleSlashUri) {
  const std::string uri = "/my_dir/index.html";
  std::string uri_start = GetUriStart(uri);
  EXPECT_EQ(uri_start, "/my_dir");
}

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

TEST(NumberMatchesTest, MatchFunction){
  std::string str1 = "asdmatches";
  std::string str2 = "abcmat";
  unsigned int expected = 1;
  
  EXPECT_EQ(expected, NumberMatches(str1, str2));
}

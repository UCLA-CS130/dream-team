#include "gtest/gtest.h"
#include "../src/http_message.h"
#include "../src/http_entity.h"

TEST(HttpMessageTest, MessageSerialization) {
  const std::string start_line = "random first line";
  const std::string header1 = "key: value";
  const std::string header2 = "key2: value2";
  const std::string delim = "\r\n";
  const std::string ser_message = 
    start_line + delim + 
    header1 + delim + 
    header2 + delim + delim;
  
  HttpHeader parsed_header1("key", "value");
  HttpHeader parsed_header2("key2", "value2");
  
  HttpMessage message(start_line);
  message.AddHeader(parsed_header1);
  message.AddHeader(parsed_header2);
  // TODO: add test HttpEntity body
  
  EXPECT_EQ(ser_message, message.Serialize());
}

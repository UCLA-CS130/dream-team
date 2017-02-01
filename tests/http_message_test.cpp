#include "gtest/gtest.h"
#include "../src/http_message.h"

TEST(HttpMessageTest, MessageSerialization) {
  const std::string start_line = "random first line";
  const std::string header1 = "key; value";
  const std::string header2 = "key2; value2";
  const std::string body = "this is a random body that should stay the same";
  const std::string delim = "\r\n";
  const std::string ser_message = 
    start_line + delim + 
    header1 + delim + 
    header2 + delim + delim +
    body;
  
  HttpHeader parsed_header1("key", "value");
  HttpHeader parsed_header2("key2", "value2");
  
  HttpMessage message(start_line);
  message.AddHeader(parsed_header1);
  message.AddHeader(parsed_header2);
  message.SetBody(body);
  
  EXPECT_EQ(ser_message, message.Serialize());
}

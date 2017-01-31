#include "gtest/gtest.h"
#include "../src/HttpHeader.h"

TEST(HttpMessageTest, HeaderSerialization) {
  const std::string content_type_ser = "Content-Type; text/plain";
  
  HttpHeader header("Content-Type", "text/plain");
  EXPECT_EQ(header.Serialize(), content_type_ser);
}

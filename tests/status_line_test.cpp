#include "gtest/gtest.h"
#include "../src/status_line.h"

TEST(StatusLineTest, StatusSerialization) {
  const std::string protocol_version = "HTTP/1.1";
  const unsigned status_code = 200;
  const std::string status_message = "OK";

  const std::string status_line = protocol_version + " " + std::to_string(status_code) + " " + status_message;
  StatusLine parsed_status_line(protocol_version, status_code);

  EXPECT_EQ(parsed_status_line.Serialize(), status_line);
}

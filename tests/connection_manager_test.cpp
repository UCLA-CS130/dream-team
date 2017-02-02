#include "gtest/gtest.h"
#include "../src/connection_manager.h"

TEST(ConnectionManagerTest, ValidGetRequest) {
  const std::string valid_get_req = 
    "GET /random_res HTTP/1.1\r\n\r\n";

  const std::string expected_resp = 
    "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n" + valid_get_req;
  
  const unsigned random_port = 10;
  ConnectionManager manager(random_port);

  HttpResponse resp = manager.ProcessGetRequest(valid_get_req);
  EXPECT_EQ(resp.Serialize(), expected_resp);
}

TEST(ConnectionManagerTest, InvalidGetRequest) {

}

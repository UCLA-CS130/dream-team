#include "gtest/gtest.h"
#include "../src/http_message.h"
#include "../src/http_entity.h"

TEST(HttpEntityTest, BasicTest){
  const std::string uri = "/fakePath/index.php";
  
  HttpEntity entity(uri);
  
  EXPECT_EQ(uri, entity.GetUri());
  // TODO: test HttpEntity::OpenStream
}

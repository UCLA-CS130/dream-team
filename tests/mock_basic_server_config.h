#ifndef MockParsedConfig_h
#define MockParsedConfig_h

#include "gmock/gmock.h"
#include "../src/basic_server_config.h"

class MockBasicServerConfig : public BasicServerConfig {
public:
  MOCK_METHOD0(GetPortNumber, unsigned());
};

#endif

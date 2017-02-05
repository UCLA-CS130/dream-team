#ifndef MockParsedConfig_h
#define MockParsedConfig_h

#include "gmock/gmock.h"
#include "../src/parsed_config.h"

class MockParsedConfig : public ParsedConfig {
public:
  MOCK_METHOD0(GetPortNumber, unsigned());
};

#endif
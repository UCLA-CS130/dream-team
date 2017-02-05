#ifndef ParsedConfig_h
#define ParsedConfig_h

#include <string>
#include <vector>
#include <stdexcept>
#include "nginx-configparser/config_parser.h"

#define INVALID_PORT 0
#define MAX_PORT 65535

class ParsedConfig {
public:
  ParsedConfig() {}
  ParsedConfig(NginxConfig* config);
  virtual unsigned GetPortNumber();
  std::string GetRootDirectory();
private:
  bool initialize(NginxConfig* config);
  bool initParsedConfig(NginxConfig* config);
  unsigned port_number_;
  std::string root_dir_;
};

#endif
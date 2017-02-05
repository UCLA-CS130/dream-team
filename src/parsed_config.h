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
  ParsedConfig(NginxConfig* config);
  unsigned getPortNumber();
  std::string getRootDirectory();
private:
  bool initialize(NginxConfig* config);
  bool initParsedConfig(NginxConfig* config);
  unsigned port_number_;
  std::string root_dir_;
};

#endif
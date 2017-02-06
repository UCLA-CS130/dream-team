#ifndef ParsedConfig_h
#define ParsedConfig_h

#include <string>
#include <vector>
#include "nginx-configparser/config_parser.h"

class ParsedConfig {
public:
  ParsedConfig() {}
  ParsedConfig(NginxConfig* config);
  std::vector<std::shared_ptr<NginxConfigStatement>> FilterStatements(NginxConfig* root, 
								      std::string search_statement);
  std::vector<std::string> GetStatementValues(NginxConfig* root, std::string search_statement);
  std::string GetStatementValue(NginxConfig* root, std::string search_statement);
  NginxConfig* GetConfig();
private:
  NginxConfig* config_;
};

#endif

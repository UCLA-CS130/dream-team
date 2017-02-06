//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef BasicServerConfig_h
#define BasicServerConfig_h

#include <map>
#include "parsed_config.h"

class BasicServerConfig : public ParsedConfig {
 public:
  BasicServerConfig(NginxConfig* config);
  bool Init();

  unsigned GetPortNumber();
  std::string GetEchoPath();
  std::string MapUserToHostUrl(std::string user_url);
 private:
  unsigned port_number_;
  std::string echo_path_;
  std::map<std::string, std::string> root_url_paths_;
  
  bool InitPortNumber(NginxConfig* config);
  bool InitEchoPath(NginxConfig* config);
  bool InitRootUrlPaths(NginxConfig* config);
};

#endif

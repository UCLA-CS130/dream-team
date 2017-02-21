//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef BasicServerConfig_h
#define BasicServerConfig_h

#include <map>
#include "parsed_config.h"
#include "request_handler.h"

class BasicServerConfig : public ParsedConfig {
 public:
  BasicServerConfig(NginxConfig* config);
  BasicServerConfig(){} // constructor for mocking purposes
  bool Init();

  unsigned GetPortNumber();
  RequestHandler* GetRequestHandlerFromUri(std::string uri);
 private:
  unsigned port_number_;
  std::map<std::string, RequestHandler*> uri_to_request_handler_;
  RequestHandler* default_handler_;

  RequestHandler* BuildHandlerForUri(std::string uri, std::string handler_id, std::string root_dir);
  bool InitPortNumber(NginxConfig* config);
  bool InitRequestHandlers(NginxConfig* config);
};

#endif

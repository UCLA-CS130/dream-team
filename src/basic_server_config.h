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
  BasicServerConfig() {} // constructor for mocking purposes
  bool Init();

  unsigned GetPortNumber();
  RequestHandler* GetRequestHandlerFromUri(std::string uri);
 private:
  unsigned port_number_;
  std::map<std::string, std::unique_ptr<RequestHandler>> uri_to_request_handler_;
  std::unique_ptr<RequestHandler> default_handler_;
  
  bool InitPortNumber(NginxConfig* config);
  bool InitRequestHandlers(NginxConfig* config);

  std::string GetLongestMatchingUri(std::string client_uri);
  std::unique_ptr<RequestHandler> BuildHandlerForUri(std::string uri, 
						     std::string handler_id, 
						     NginxConfig* child_block);
};

#endif

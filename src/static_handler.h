//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef StaticHandler_h
#define StaticHandler_h

#include "request_handler.h"

class StaticHandler : public RequestHandler {
 public:
  virtual RequestHandler::Status Init(const std::string& uri_prefix,
				      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
					       Response* response) override;
 private:
  std::string root_uri_;
};

REGISTER_REQUEST_HANDLER(StaticHandler);

#endif

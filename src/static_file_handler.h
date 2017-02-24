//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef StaticFileHandler_h
#define StaticFileHandler_h

#include "request_handler.h"

class StaticFileHandler : public RequestHandler {
 public:
  virtual RequestHandler::Status Init(const std::string& uri_prefix,
				      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
					       Response* response) override;
 private:
  std::string root_uri_;
};

REGISTER_REQUEST_HANDLER(StaticFileHandler);

#endif

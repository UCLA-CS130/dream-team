//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef StatusHandler_h
#define StatusHandler_h

#include <map>
#include "request_handler.h"

class StatusHandler : public RequestHandler {
 public:  
  virtual RequestHandler::Status Init(const std::string& uri_prefix,
				      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
					       Response* response) override;
};


REGISTER_REQUEST_HANDLER(StatusHandler);

#endif

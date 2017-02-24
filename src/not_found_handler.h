//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef NotFoundHandler_h
#define NotFoundHandler_h

#include "request_handler.h"

class NotFoundHandler : public RequestHandler {
 public:
  virtual RequestHandler::Status Init(const std::string& uri_prefix,
				      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
					       Response* response) override;  
};

REGISTER_REQUEST_HANDLER(NotFoundHandler);

#endif

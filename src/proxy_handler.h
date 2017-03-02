//
// Created by Michael Chen on 2/28/17.
// Copyright © 2017 Chen. All rights reserved.
//

#ifndef ProxyHandler_h
#define ProxyHandler_h

#include "request_handler.h"

const int MAX_REDIRECTS = 20;

class ProxyHandler : public RequestHandler {
 public:
  virtual RequestHandler::Status Init(const std::string& uri_prefix,
				      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
					       Response* response) override;

  RequestHandler::Status HandleRequestHelper(const Request& request,
                 Response* response, int count);
 private:
  std::string proxy_host_;
  std::string proxy_port_;
  std::string redirect_uri_;
};

REGISTER_REQUEST_HANDLER(ProxyHandler);

#endif

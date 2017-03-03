//
// Created by Michael Chen on 2/28/17.
// Copyright © 2017 Chen. All rights reserved.
//

#ifndef ProxyHandler_h
#define ProxyHandler_h

#include "request_handler.h"
#include <boost/asio.hpp>

const int MAX_REDIRECTS = 20;

class ProxyHandler : public RequestHandler {
 public:
  virtual RequestHandler::Status Init(const std::string& uri_prefix,
                                      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
                                               Response* response) override;

  RequestHandler::Status HandleRequestHelper(const Request& request,
                                             Response* response,
                                             int count);
 private:
  std::string proxy_host_;
  std::string proxy_port_;
  std::string redirect_uri_;
  void SendRequest(const Request& request, Response* response, int count, boost::asio::ip::tcp::socket* socket);
  RequestHandler::Status HandleHeaders(const Request& request, Response* response, int count, boost::asio::ip::tcp::socket* socket, std::string* body);
  void HandleBody(const Request& request, Response* response, std::string* body);

};

REGISTER_REQUEST_HANDLER(ProxyHandler);

#endif

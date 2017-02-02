//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef ConnectionManager_h
#define ConnectionManager_h

#include <string>
#include <boost/asio.hpp>
#include "http_response.h"

class ConnectionManager {
 public:
  ConnectionManager(unsigned port_number);
  void RunTcpServer();
  HttpResponse ProcessGetRequest(std::string raw_request);
  HttpResponse ProcessBadRequest(std::string raw_request);
 private:
  void AttachDefaultContentTypeHeader(HttpResponse &resp);
  void StreamHttpResponse(boost::asio::ip::tcp::socket &socket, const HttpResponse &resp);
  unsigned port_number_;
};

#endif

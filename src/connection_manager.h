//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef ConnectionManager_h
#define ConnectionManager_h

#include <string>
#include <boost/asio.hpp>
#include <fstream>

#include "utils.h"
#include "http_response.h"
#include "http_request.h"

class ConnectionManager {
 public:
  ConnectionManager(unsigned port_number);
  void RunTcpServer();
  HttpResponse ProcessGetRequest(const HttpRequest& request);
  HttpResponse ProcessBadRequest(unsigned status_code);
 private:
  void AttachDefaultContentTypeHeader(HttpResponse& resp);
  void StreamHttpResponse(boost::asio::ip::tcp::socket& socket, const HttpResponse& resp);
  unsigned port_number_;
};

#endif

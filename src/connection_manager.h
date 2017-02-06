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
#include "parsed_config.h"

class ConnectionManager {
 public:
  ConnectionManager(ParsedConfig* parsed_config);
  void RunTcpServer();
  HttpResponse ProcessGetRequest(const HttpRequest& request);
  HttpResponse ProcessBadRequest(unsigned status_code);
  ParsedConfig* GetParsedConfig();
 private:
  void AttachDefaultContentTypeHeader(HttpResponse& resp);
  void StreamHttpResponse(boost::asio::ip::tcp::socket& socket, const HttpResponse& resp);
  ParsedConfig* parsed_config_;
};

#endif

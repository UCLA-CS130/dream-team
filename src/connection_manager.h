//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef ConnectionManager_h
#define ConnectionManager_h

#include <string>
#include <memory>
#include <fstream>
#include <boost/asio.hpp>
#include "utils.h"
#include "response.h"
#include "request.h"
#include "request_handler.h"
#include "basic_server_config.h"

class ConnectionManager {
 public:
  ConnectionManager(BasicServerConfig* parsed_config);

  void RunTcpServer();
  RequestHandler::Status HandleRequest(const Request& request, Response* response);
 private:
  void QueueClientThread(std::unique_ptr<boost::asio::ip::tcp::socket> socket);
  void ProcessClientConnection(std::unique_ptr<boost::asio::ip::tcp::socket> socket);
  void StreamHttpResponse(boost::asio::ip::tcp::socket& socket, const Response& resp);
  BasicServerConfig* parsed_config_;
};

#endif

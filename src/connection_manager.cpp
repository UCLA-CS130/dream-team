//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <iostream>
#include <thread>
#include "connection_manager.h"

ConnectionManager::ConnectionManager(BasicServerConfig* parsed_config, unsigned port_number) :
  parsed_config_(parsed_config) {
    port_number_ = port_number;
  }

// Boost usage inspired by https://github.com/egalli64/thisthread/blob/master/asio/tcpIpCs.cpp
void ConnectionManager::RunTcpServer() {
  std::cout << "Starting server" << std::endl;

  boost::asio::ip::tcp::acceptor acceptor(aios_,
					  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_number_));

  while (true) {
    try {
      auto socket = std::unique_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(aios_));
      acceptor.accept(*socket);
      QueueClientThread(std::move(socket));
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  }
}

void ConnectionManager::QueueClientThread(std::unique_ptr<boost::asio::ip::tcp::socket> socket) {
  std::thread client_req_handler(&ConnectionManager::OnSocketReady, this, std::move(socket));
  client_req_handler.detach();
}

void ConnectionManager::OnSocketReady(std::unique_ptr<boost::asio::ip::tcp::socket> socket) {
  ProcessClient(*socket);
}

RequestHandler::Status ConnectionManager::HandleRequest(const Request& req, Response* response) {
  std::string req_uri = req.uri();
  RequestHandler* handler = parsed_config_->GetRequestHandlerFromUri(req_uri);
  if (handler == nullptr) {
    return RequestHandler::UNKNOWN_HANDLER;
  }

  return handler->HandleRequest(req, response);
}

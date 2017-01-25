//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "ConnectionManager.h"
#include "HttpResponse.h"

const std::string PROTOCOL_VERSION = "Http/1.1";
const std::string SUCCESS_MESSAGE = "OK";
const unsigned SUCCESS = 200;

ConnectionManager::ConnectionManager(unsigned port_number) {
  port_number_ = port_number;
}

// Inspired by https://github.com/egalli64/thisthread/blob/master/asio/tcpIpCs.cpp
void ConnectionManager::RunTcpServer() {
  boost::asio::io_service aios;
  boost::asio::ip::tcp::acceptor acceptor(aios, 
					  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_number_));

  while (true) {
    boost::asio::ip::tcp::socket socket(aios);
    acceptor.accept(socket);

    std::stringstream message_stream;
    boost::asio::streambuf buffer;
    boost::system::error_code error;
    size_t len = read_until(socket, buffer, REQUEST_DELIMITER, error);
       
    if (len) {
      message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
      StatusLine resp_status(PROTOCOL_VERSION, SUCCESS, SUCCESS_MESSAGE);
      HttpResponse response(resp_status);
      response.AddHeader("Content-Type: text/plain");
      response.SetBody(message_stream.str());
      
      boost::asio::write(socket, boost::asio::buffer(response.Serialize()));
    }
  }
}

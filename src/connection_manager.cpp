//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <iostream>
#include "connection_manager.h"

const std::string PROTOCOL_VERSION = "HTTP/1.1";

const std::string SUCCESS_MESSAGE = "OK";
const unsigned SUCCESS = 200;

const std::string BAD_REQUEST_MESSAGE = "Bad Request";
const unsigned BAD_REQUEST = 400;

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
    
    std::unique_ptr<StatusLine> resp_status;
    std::string resp_body = "";

    if (len) {
      message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
      resp_body = message_stream.str();
      resp_status.reset(new StatusLine(PROTOCOL_VERSION, SUCCESS, SUCCESS_MESSAGE));
    } else {
      resp_status.reset(new StatusLine(PROTOCOL_VERSION, BAD_REQUEST, BAD_REQUEST_MESSAGE));
    }
    
    HttpHeader content_type("Content-Type", "text/plain");

    HttpResponse response(*resp_status);
    response.AddHeader(content_type);
    response.SetBody(resp_body);
    boost::asio::write(socket, boost::asio::buffer(response.Serialize()));
  }
}

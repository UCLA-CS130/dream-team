//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <iostream>
#include <thread>
#include "connection_manager.h"

ConnectionManager::ConnectionManager(BasicServerConfig* parsed_config) {
  parsed_config_ = parsed_config;
}

// Boost usage inspired by https://github.com/egalli64/thisthread/blob/master/asio/tcpIpCs.cpp
void ConnectionManager::RunTcpServer() {
  std::cout << "Starting server" << std::endl; 

  unsigned port = parsed_config_->GetPortNumber();
  boost::asio::ip::tcp::acceptor acceptor(aios_, 
					  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
  
  while (true) {
    auto socket = std::unique_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(aios_));
    acceptor.accept(*socket);
    QueueClientThread(std::move(socket));    
  }
}

void ConnectionManager::QueueClientThread(std::unique_ptr<boost::asio::ip::tcp::socket> socket) {
  std::thread client_req_handler(&ConnectionManager::ProcessClientConnection, this, std::move(socket));
  client_req_handler.detach();
}

void ConnectionManager::ProcessClientConnection(std::unique_ptr<boost::asio::ip::tcp::socket> socket) {
  boost::asio::ssl::context context(aios_, boost::asio::ssl::context::sslv23);
  context.set_options(boost::asio::ssl::context::default_workarounds |
  		      boost::asio::ssl::context::no_sslv2 | 
		      boost::asio::ssl::context::single_dh_use);
  
  context.use_certificate_chain_file("/etc/ssl/certs/dt-server.pem");
  context.use_private_key_file("/etc/ssl/certs/dt-server.key", boost::asio::ssl::context::pem);

  boost::asio::ssl::stream<boost::asio::ip::tcp::socket&> ssl_sock(*socket, context);
  ssl_sock.handshake(boost::asio::ssl::stream_base::server);

  std::stringstream message_stream;
  boost::asio::streambuf buffer;
  boost::system::error_code error;

  size_t len = read_until(ssl_sock, buffer, REQUEST_DELIMITER, error);      

  if (len) {
    message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
      
    std::string raw_request = message_stream.str();
    std::cout << "Incoming Request: " << std::endl << raw_request << std::endl;
      
    Response response;
    std::unique_ptr<Request> req = Request::Parse(raw_request);             
    RequestHandler::Status handle_resp = HandleRequest(*req, &response); 
      
    if (handle_resp != RequestHandler::OK) {
      std::cerr << "Error " << handle_resp << " while handling " << raw_request << std::endl;	
      response.SetStatus(Response::SERVER_ERROR);
    }
      
    parsed_config_->UpdateStatusHandlers(*req, response);
    StreamHttpResponse(ssl_sock, response);
  }
}

RequestHandler::Status ConnectionManager::HandleRequest(const Request& req, Response* response) {
  std::string req_uri = req.uri();
  RequestHandler* handler = parsed_config_->GetRequestHandlerFromUri(req_uri);  
  if (handler == nullptr) {
    return RequestHandler::UNKNOWN_HANDLER;
  }

  return handler->HandleRequest(req, response);
}

void ConnectionManager::StreamHttpResponse(boost::asio::ssl::stream<boost::asio::ip::tcp::socket&>& socket, 
					   const Response& resp) {  
  std::string ser_resp = resp.ToString();
  std::cout << "RESPONSE: " << ser_resp << std::endl;
  boost::asio::write(socket, boost::asio::buffer(ser_resp)); 
}

//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <iostream>
#include <thread>
#include "connection_manager.h"

ConnectionManager::ConnectionManager(BasicServerConfig* parsed_config) :
  parsed_config_(parsed_config) {}

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
  std::thread client_req_handler(&ConnectionManager::OnSocketReady, this, std::move(socket));
  client_req_handler.detach();
}

void ConnectionManager::OnSocketReady(std::unique_ptr<boost::asio::ip::tcp::socket> socket) { 
  ProcessClient(*socket);
}

template<typename AbstractSocket>
void ConnectionManager::ProcessClient(AbstractSocket& sock) {
  Response response;
  std::unique_ptr<Request> req = ReadHttpRequest(sock);
  RequestHandler::Status handle_resp = HandleRequest(*req, &response); 
  
  if (handle_resp != RequestHandler::OK) {
    std::cerr << "Error " << handle_resp << " while handling " << req->raw_request() << std::endl;	
    response.SetStatus(Response::SERVER_ERROR);
  }
  
  parsed_config_->UpdateStatusHandlers(*req, response);
  StreamHttpResponse(sock, response);
}

RequestHandler::Status ConnectionManager::HandleRequest(const Request& req, Response* response) {
  std::string req_uri = req.uri();
  RequestHandler* handler = parsed_config_->GetRequestHandlerFromUri(req_uri);  
  if (handler == nullptr) {
    return RequestHandler::UNKNOWN_HANDLER;
  }

  return handler->HandleRequest(req, response);
}

template<typename ReadStream>
std::unique_ptr<Request> ConnectionManager::ReadHttpRequest(ReadStream& read_stream) {
  std::stringstream message_stream;
  boost::asio::streambuf buffer;
  boost::system::error_code error;

  size_t len = read_until(read_stream, buffer, REQUEST_DELIMITER, error);      
  message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
  
  std::string raw_request = message_stream.str();
  std::cout << "Incoming Request: " << std::endl << raw_request << std::endl;      
  return Request::Parse(raw_request);                
}

template<typename WriteStream>
void ConnectionManager::StreamHttpResponse(WriteStream& write_stream, 
					   const Response& resp) {  
  std::string ser_resp = resp.ToString();
  std::cout << "RESPONSE: " << ser_resp << std::endl;
  boost::asio::write(write_stream, boost::asio::buffer(ser_resp)); 
}

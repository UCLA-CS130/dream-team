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

// Boost usage inspired by https://github.com/egalli64/thisthread/blob/master/asio/tcpIpCs.cpp
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
      
      string raw_request = message_stream.str();
      HttpRequest req = ProcessGetRequest(message_stream.str());
      
      // use req to create response object
      // use StreamHttpResponse to send response object back to client
      HttpResponse resp = ProcessBadRequest("");
      StreamHttpResponse(socket, resp);
    } else {
      HttpResponse resp = ProcessBadRequest("");
      StreamHttpResponse(socket, resp);
    }
  }
}


HttpRequest ConnectionManager::ProcessGetRequest(const std::string raw_request) {
  std::string method, uri, version;
  std::vector<string> tokens;
  std::vector<string> request_line_tokens;
  string request_line;
  
  tokenize(rawMessage, tokens, "\r\n");
  
  if (tokens.size() > 0) {
    request_line = tokens[0];
  } else {
    throw ResponseException(400);
  }
  
  tokenize(request_line, request_line_tokens);
  if (request_line_tokens.size() == 3) {
    method = request_line_tokens[0];
    uri = request_line_tokens[1];
    version = request_line_tokens[2];
  } else {
    throw ResponseException(400);
  }
  
  HttpRequestLine request_line(method, uri, version);
  HttpRequest request(request_line);
  
  for(int i = 1; i < tokens.size(); i++){
    if(tokens[i] == ""){
      if(i < tokens.size() - 1)
        request.SetBody(tokens[tokens.size() - 1]);
      break;
    }
    vector<std::string> keyValue;
    tokenize(tokens[i], keyValue, ": ");
    if(keyValue.size() == 2){
      HttpHeader http_header(keyValue[0], keyValue[1]);
      request.AddHeader(http_header);
    }
  }
  
  return request;
}

HttpResponse ConnectionManager::ProcessBadRequest(std::string raw_request) {
  StatusLine err_line(PROTOCOL_VERSION, BAD_REQUEST, BAD_REQUEST_MESSAGE);
     
  HttpResponse err_resp(err_line);
  AttachDefaultContentTypeHeader(err_resp);
  return err_resp;
}

void ConnectionManager::AttachDefaultContentTypeHeader(HttpResponse &resp) {
  HttpHeader content_type("Content-Type", "text/plain");
  resp.AddHeader(content_type);
}

void ConnectionManager::StreamHttpResponse(boost::asio::ip::tcp::socket &socket, const HttpResponse &resp) {
  boost::asio::write(socket, boost::asio::buffer(resp.Serialize())); 
}

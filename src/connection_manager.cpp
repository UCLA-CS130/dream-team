//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <iostream>
#include "connection_manager.h"

const std::string PROTOCOL_VERSION = "HTTP/1.1";
const std::string CONTENT_TYPE_HEADER = "Content-Type";

ConnectionManager::ConnectionManager(BasicServerConfig* parsed_config) {
  parsed_config_ = parsed_config;
}

// Boost usage inspired by https://github.com/egalli64/thisthread/blob/master/asio/tcpIpCs.cpp
void ConnectionManager::RunTcpServer() {
  std::cout << "Starting server" << std::endl;
  
  unsigned port = parsed_config_->GetPortNumber();
  boost::asio::io_service aios;
  boost::asio::ip::tcp::acceptor acceptor(aios, 
					  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

  while (true) {
    boost::asio::ip::tcp::socket socket(aios);
    acceptor.accept(socket);
       
    std::stringstream message_stream;
    boost::asio::streambuf buffer;
    boost::system::error_code error;
    size_t len = read_until(socket, buffer, REQUEST_DELIMITER, error);      

    if (len) {
      message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
      
      std::string raw_request = message_stream.str();
      std::cout << raw_request << std::endl;

      HttpRequest req = parse_message(raw_request);
      HttpResponse resp = ProcessGetRequest(req);
      
      /*if (parsed_config_->IsRequestEcho(req.GetRequestLine().GetUri())) {
      	boost::asio::write(socket, boost::asio::buffer(resp.Serialize()));
      	boost::asio::write(socket, boost::asio::buffer("\r\n" + raw_request));
      } else {	
        StreamHttpResponse(socket, resp);
      } */     
    } else {
      HttpResponse resp = ProcessBadRequest(BAD_REQUEST);
      StreamHttpResponse(socket, resp);
    }
  }
}

HttpResponse ConnectionManager::ProcessGetRequest(const HttpRequest& request) {  
  StatusLine status(PROTOCOL_VERSION, SUCCESS);  
  
  HttpRequestLine request_line = request.GetRequestLine();
  HttpHeader content_type_header(CONTENT_TYPE_HEADER, request_line.GetContentType());
 
  std::string routed_url = "";

  HttpEntity entity(routed_url);

  HttpResponse response(status);  
  response.AddHeader(content_type_header);
  response.SetBody(entity); 
  return response;
}

HttpResponse ConnectionManager::ProcessBadRequest(unsigned status_code) {
  StatusLine err_line(PROTOCOL_VERSION, status_code);
     
  HttpResponse err_resp(err_line);
  AttachDefaultContentTypeHeader(err_resp);
  return err_resp;
}

void ConnectionManager::AttachDefaultContentTypeHeader(HttpResponse& resp) {
  HttpHeader content_type(CONTENT_TYPE_HEADER, "text/plain");
  resp.AddHeader(content_type);
}

void ConnectionManager::StreamHttpResponse(boost::asio::ip::tcp::socket& socket, const HttpResponse& resp) {
  boost::asio::streambuf response;
  std::ostream response_stream(&response);
  
  HttpEntity entity = resp.GetBody();
  std::ifstream resp_file;
  if (entity.OpenStream(&resp_file)) {
    boost::asio::write(socket, boost::asio::buffer(resp.Serialize())); 
    
    char buff[512];
    while (resp_file.read(buff, sizeof(buff)).gcount() > 0) {
      boost::asio::write(socket, boost::asio::buffer(buff, resp_file.gcount()));
    }

    resp_file.close();
  } else {
    HttpResponse bad_req = ProcessBadRequest(FILE_NOT_FOUND);
    boost::asio::write(socket, boost::asio::buffer(bad_req.Serialize()));
  }
}

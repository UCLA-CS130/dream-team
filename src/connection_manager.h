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
  ConnectionManager(BasicServerConfig* parsed_config, unsigned port_number);
  void RunTcpServer();
  RequestHandler::Status HandleRequest(const Request& request, Response* response);

 protected:
  virtual void OnSocketReady(std::unique_ptr<boost::asio::ip::tcp::socket> socket);

  template<typename AbstractSocket>
  void ProcessClient(AbstractSocket& sock) {
    Response response;
    std::unique_ptr<Request> req = ConnectionManager::ReadHttpRequest(sock);
    RequestHandler::Status handle_resp = ConnectionManager::HandleRequest(*req, &response);

    if (handle_resp != RequestHandler::OK) {
      std::cerr << "Error " << handle_resp << " while handling " << req->raw_request() << std::endl;
      response.SetStatus(Response::SERVER_ERROR);
    }

    parsed_config_->UpdateStatusHandlers(*req, response);
    StreamHttpResponse(sock, response);
  }

  boost::asio::io_service aios_;
  BasicServerConfig* parsed_config_;
  unsigned port_number_;

 private:
  void QueueClientThread(std::unique_ptr<boost::asio::ip::tcp::socket> socket);

  template<typename ReadStream>
  std::unique_ptr<Request> ReadHttpRequest(ReadStream& read_stream) {
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
  void StreamHttpResponse(WriteStream& write_stream,
			  const Response& resp) {
    std::string ser_resp = resp.ToString();
    std::cout << "RESPONSE: " << ser_resp << std::endl;
    boost::asio::write(write_stream, boost::asio::buffer(ser_resp));
  }
};

#endif

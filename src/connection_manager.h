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
    
 protected:  
  virtual void OnSocketReady(std::unique_ptr<boost::asio::ip::tcp::socket> socket);  
  
  template<typename AbstractSocket>
  void ProcessClient(AbstractSocket& sock);

  boost::asio::io_service aios_;
  BasicServerConfig* parsed_config_;

 private:
  void QueueClientThread(std::unique_ptr<boost::asio::ip::tcp::socket> socket);  

  template<typename ReadStream>
  std::unique_ptr<Request> ReadHttpRequest(ReadStream& read_stream);
  
  template<typename WriteStream>
  void StreamHttpResponse(WriteStream& write_stream,
			  const Response& resp);
};

#endif

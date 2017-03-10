//
// Created by Usama Riaz on 3/9/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef SSlConnectionManager_h
#define SSLConnectionManager_h

#include <boost/asio/ssl.hpp>
#include "connection_manager.h"

class SSLConnectionManager : public ConnectionManager {
 public:
  SSLConnectionManager(BasicServerConfig* parsed_config, boost::asio::ssl::context* context_);

 protected:
  virtual void OnSocketReady(std::unique_ptr<boost::asio::ip::tcp::socket> socket) override; 

 private:
  boost::asio::ssl::context* context_;
};

#endif

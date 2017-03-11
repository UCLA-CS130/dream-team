//
// Created by Usama Riaz on 3/9/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "ssl_connection_manager.h"

SSLConnectionManager::SSLConnectionManager(BasicServerConfig* parsed_config) 
  : ConnectionManager::ConnectionManager(parsed_config), context_(aios_, boost::asio::ssl::context::sslv23) {  
  context_.set_options(boost::asio::ssl::context::default_workarounds |
		       boost::asio::ssl::context::no_sslv2 | 
		       boost::asio::ssl::context::single_dh_use);
  
  context_.use_certificate_chain_file("tests/certs/dt-server.pem");
  context_.use_private_key_file("tests/certs/dt-server.key", boost::asio::ssl::context::pem);
}

void SSLConnectionManager::OnSocketReady(std::unique_ptr<boost::asio::ip::tcp::socket> socket) {
  boost::asio::ssl::stream<boost::asio::ip::tcp::socket&> ssl_sock(*socket, context_);
  ssl_sock.handshake(boost::asio::ssl::stream_base::server);
  ConnectionManager::ProcessClient(ssl_sock);
}

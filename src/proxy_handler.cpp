//
// Created by Michael Chen on 2/28/17.
// Copyright © 2017 Chen. All rights reserved.
//

#include "proxy_handler.h"
#include "parsed_config.h"

RequestHandler::Status ProxyHandler::Init(const std::string& uri_prefix,
					 const NginxConfig& config) {
  uri_prefix_ = uri_prefix;
  ParsedConfig parser;
  proxy_host_ = parser.GetStatementValue(&config, "host");
  if (proxy_host_.length() == 0) {
    return RequestHandler::INVALID_CONFIG;
  }
  
  proxy_port_ = parser.GetStatementValue(&config, "port");
  if (proxy_port_.length() == 0) {
    return RequestHandler::INVALID_CONFIG;
  }

  return RequestHandler::OK;
}

RequestHandler::Status ProxyHandler::HandleRequest(const Request &request, 
						  Response *response) {

  std::cout << "Host: " << proxy_host_ << std::endl;
  std::cout << "Port: " << proxy_port_ << std::endl;
  return RequestHandler::OK;
}

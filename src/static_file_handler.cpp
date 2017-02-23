//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <sstream>
#include <fstream>
#include <streambuf>
#include "static_file_handler.h"
#include "file_not_found_handler.h"
#include "parsed_config.h"

RequestHandler::Status StaticFileHandler::Init(const std::string& uri_prefix,
					       const NginxConfig& config) {
  uri_prefix_ = uri_prefix;
  
  ParsedConfig parser;
  root_uri_ = parser.GetStatementValue(&config, "root");
  if (root_uri_ == "") {
    return RequestHandler::INVALID_CONFIG;
  }

  return RequestHandler::OK;
}

RequestHandler::Status StaticFileHandler::HandleRequest(const Request& request,
							Response* response) {
  std::string client_uri = request.uri();
  std::string internal_uri = client_uri.replace(0, uri_prefix_.length(), root_uri_);
  
  std::ifstream file_stream(internal_uri);
  if (!file_stream.good()) {
    FileNotFoundHandler not_found_handler;
    return not_found_handler.HandleRequest(request, response);
  }

  std::stringstream buff;
  buff << file_stream.rdbuf();  
  std::string body = buff.str();
  
  AttachTextPlainContentTypeHeader(response);
  response->SetStatus(Response::OK);
  response->SetBody(body);
  return RequestHandler::OK;
}

//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <map>
#include <sstream>
#include <fstream>
#include <streambuf>
#include "static_handler.h"
#include "not_found_handler.h"
#include "parsed_config.h"

std::map<std::string, std::string> content_mapper =
  {{"html", "text/html"},
   {"jpg", "image/jpeg"},
   {"png", "image/png"},
   {"gif", "image/gif"},
   {"htm", "text/html"}};

RequestHandler::Status StaticHandler::Init(const std::string& uri_prefix,
					       const NginxConfig& config) {
  uri_prefix_ = uri_prefix;
  
  ParsedConfig parser;
  root_uri_ = parser.GetStatementValue(&config, "root");
  if (root_uri_.length() == 0) {
    return RequestHandler::INVALID_CONFIG;
  }
  
  if (root_uri_[root_uri_.length() - 1] != '/') {
    root_uri_ += "/";
  }

  return RequestHandler::OK;
}

std::string ExtractContentType(const std::string& uri) {
  std::string extension = uri.substr(uri.find_last_of(".") + 1);
  if (content_mapper.count(extension) > 0) {
    return content_mapper[extension];
  }
  
  return RequestHandler::TYPE_TEXT_PLAIN;
}


RequestHandler::Status StaticHandler::HandleRequest(const Request& request,
							Response* response) {
  std::string client_uri = request.uri();
  std::string internal_uri = client_uri.replace(0, uri_prefix_.length(), root_uri_);  

  std::ifstream file_stream(internal_uri);
  if (!file_stream.good()) {
    NotFoundHandler not_found_handler;
    return not_found_handler.HandleRequest(request, response);
  }

  std::stringstream buff;
  buff << file_stream.rdbuf();  
  std::string body = buff.str();
  
  std::string content_type = ExtractContentType(internal_uri);
  response->AddHeader(RequestHandler::CONTENT_TYPE_HEADER, content_type);
  response->SetStatus(Response::OK);
  response->SetBody(body);
  return RequestHandler::OK;
}

//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "echo_handler.h"

RequestHandler::Status EchoHandler::Init(const std::string& prefix,
					 const NginxConfig& config) {
  uri_prefix_ = prefix;
  return RequestHandler::OK;
}

RequestHandler::Status EchoHandler::HandleRequest(const Request &request, 
						  Response *response) {
  AttachTextPlainContentTypeHeader(response);
  response->SetStatus(Response::OK);
  response->SetBody(request.raw_request());
  return RequestHandler::OK;
}

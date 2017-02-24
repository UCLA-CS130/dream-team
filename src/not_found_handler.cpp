//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "not_found_handler.h"

RequestHandler::Status NotFoundHandler::Init(const std::string& uri_prefix,
						 const NginxConfig& config) {
  return RequestHandler::OK;
}
  
RequestHandler::Status NotFoundHandler::HandleRequest(const Request& request,
							  Response* response) {
  AttachTextPlainContentTypeHeader(response);
  response->SetStatus(Response::NOT_FOUND);
  return RequestHandler::OK;
}

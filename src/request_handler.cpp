//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "request_handler.h"

std::map<std::string, RequestHandler* (*)(void)>* request_handler_builders = nullptr;

const std::string RequestHandler::CONTENT_TYPE_HEADER = "Content-Type";
const std::string RequestHandler::TYPE_TEXT_PLAIN = "text/plain";

RequestHandler* RequestHandler::CreateByName(const std::string& type) {
  const auto type_and_builder = request_handler_builders->find(type);
  if (type_and_builder == request_handler_builders->end()) {
    return nullptr;
  }

  return (*type_and_builder->second)();
}

void RequestHandler::AttachTextPlainContentTypeHeader(Response* resp) {
  resp->AddHeader(CONTENT_TYPE_HEADER, TYPE_TEXT_PLAIN);
}


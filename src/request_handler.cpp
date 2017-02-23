//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "request_handler.h"

const std::string RequestHandler::CONTENT_TYPE_HEADER = "Content-Type";
const std::string RequestHandler::TYPE_TEXT_PLAIN = "text/plain";

void RequestHandler::AttachTextPlainContentTypeHeader(Response* resp) {
  resp->AddHeader(CONTENT_TYPE_HEADER, TYPE_TEXT_PLAIN);
}

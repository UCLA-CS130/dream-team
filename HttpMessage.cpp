//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "HttpMessage.h"

HttpMessage::HttpMessage(std::string start_line) {
  start_line_ = start_line;
}

void HttpMessage::AddHeader(std::string header) {
  headers_.push_back(header);
}

std::vector<std::string> HttpMessage::GetHeaders() {
  return headers_;
}

std::string HttpMessage::GetBody() {
  return body_;
}

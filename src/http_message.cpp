//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "http_message.h"

HttpMessage::HttpMessage(std::string start_line) {
  start_line_ = start_line;
}

std::string HttpMessage::Serialize() const {
  std::string serialized_output = start_line_;
  for(unsigned i = 0; i < headers_.size(); i++) {
    serialized_output += HEADER_DELIMITER + headers_[i].Serialize();
  }
  
  serialized_output += REQUEST_DELIMITER;
  serialized_output += body_;
  return serialized_output;
}

void HttpMessage::AddHeader(HttpHeader header) {
  headers_.push_back(header);
}

void HttpMessage::SetBody(std::string body) {
  body_ = body;
}

std::string HttpMessage::GetBody() {
  return body_;
}

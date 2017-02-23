//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "response.h"

void Response::SetStatus(const ResponseCode response_code) {
  response_code_ = response_code;
}

void Response::AddHeader(const std::string& header_name, const std::string& header_value) {
  headers_.push_back(make_pair(header_name, header_value));
}

void Response::SetBody(const std::string& body) {
  body_ = body;
}

std::string Response::SerializeResponseCode() const {
  switch(response_code_) {
    case ResponseCode::OK:
      return "200" + STATUS_LINE_DELIMITER + "OK";
    case ResponseCode::MOVED_PERMANENTLY:
      return "301" + STATUS_LINE_DELIMITER + "Moved Permanently";
    case ResponseCode::BAD_REQUEST:
      return "400" + STATUS_LINE_DELIMITER + "Bad Request";
    case ResponseCode::NOT_FOUND:
      return "404" + STATUS_LINE_DELIMITER + "Not Found";
    default:
      return "500" + STATUS_LINE_DELIMITER + "Server Error";
  }

  return "";
}

std::string Response::ToString() const {
  std::string serialized_output = VERSION + STATUS_LINE_DELIMITER + SerializeResponseCode();
  for(unsigned i = 0; i < headers_.size(); i++) {
    serialized_output += HEADER_DELIMITER + 
      headers_[i].first + 
      HEADER_KEY_VALUE_DELIMITER +
      headers_[i].second;
  }
  
  serialized_output += RESPONSE_DELIMITER;
  if(body_ != "") {
    serialized_output += body_;
    serialized_output += RESPONSE_DELIMITER;
  }
  
  return serialized_output;
}

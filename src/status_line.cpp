//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include <map>
#include "status_line.h"

std::map<unsigned, std::string> status_code_map = 
  {{SUCCESS, "OK"}, 
   {BAD_REQUEST, "Bad Request"},
   {FILE_NOT_FOUND, "Not Found"}};

StatusLine::StatusLine(std::string protocol_version, unsigned status_code) {
  protocol_version_ = protocol_version;
  status_code_ = status_code;
  reason_phrase_ = status_code_map[status_code];
}

std::string StatusLine::Serialize() const {
  std::string ser_status_code = std::to_string(status_code_);
  return protocol_version_ + " " + ser_status_code + " " + reason_phrase_;
}

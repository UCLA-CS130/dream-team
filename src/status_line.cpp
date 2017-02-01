//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "status_line.h"

StatusLine::StatusLine(std::string protocol_version, 
		       unsigned status_code, std::string reason_phrase) {
  protocol_version_ = protocol_version;
  status_code_ = status_code;
  reason_phrase_ = reason_phrase;
}

std::string StatusLine::Serialize() const {
  std::string ser_status_code = std::to_string(status_code_);
  return protocol_version_ + " " + ser_status_code + " " + reason_phrase_;
}

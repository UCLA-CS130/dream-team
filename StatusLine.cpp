//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "StatusLine.h"

StatusLine::StatusLine(std::string protocol_version, 
		       unsigned status_code, std::string reason_phrase) {
  protocol_version_ = protocol_version;
  status_code_ = status_code;
  reason_phrase_ = reason_phrase;
}

std::string StatusLine::GetProtocolVersion() { return protocol_version_; }
std::string StatusLine::GetReasonPhrase() { return reason_phrase_; }
unsigned StatusLine::GetStatusCode() { return status_code_; }

//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "HttpHeader.h"

HttpHeader::HttpHeader(std::string key, std::string value) 
  : key_(key), value_(value) {}

std::string HttpHeader::Serialize() {
  return key_ + "; " + value_;
}

//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "http_header.h"

HttpHeader::HttpHeader(std::string key, std::string value) 
  : key_(key), value_(value) {}

std::string HttpHeader::Serialize() const {
  return key_ + ": " + value_;
}

std::string HttpHeader::GetKey(){
  return key_;
}
std::string HttpHeader::GetValue(){
  return value_;
}

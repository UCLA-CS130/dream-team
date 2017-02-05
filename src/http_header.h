//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef HttpHeader_h
#define HttpHeader_h

#include <string>

class HttpHeader {
public:
  HttpHeader(std::string key, std::string value);
  std::string Serialize() const;
  std::string GetKey();
  std::string GetValue();
private:
  std::string key_;
  std::string value_;
};

#endif

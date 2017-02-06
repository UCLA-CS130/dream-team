//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef HttpEntity_h
#define HttpEntity_h

#include <fstream>
#include <string>

class HttpEntity {
 public:
  HttpEntity();
  HttpEntity(std::string uri);
  std::string GetUri();
  bool OpenStream(std::ifstream* out_stream) const;
 private:
  std::string uri_;
};

#endif

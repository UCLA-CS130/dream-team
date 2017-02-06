//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef StatusLine_h
#define StatusLine_h

#include <string>

const unsigned SUCCESS = 200;
const unsigned BAD_REQUEST = 400;
const unsigned FILE_NOT_FOUND = 404;

class StatusLine {
 public:
  StatusLine(std::string protocol_version, unsigned status_code);
  std::string Serialize() const;
 private:
  std::string protocol_version_;
  std::string reason_phrase_;
  unsigned status_code_;
};

#endif

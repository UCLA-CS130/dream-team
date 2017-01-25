//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef StatusLine_h
#define StatusLine_h

#include <string>

class StatusLine {
 public:
  StatusLine(std::string protocol_version, 
	     unsigned status_code, std::string reason_phrase);
  std::string Serialize() const;
  std::string GetProtocolVersion();
  std::string GetReasonPhrase();
  unsigned GetStatusCode();
 private:
  std::string protocol_version_;
  std::string reason_phrase_;
  unsigned status_code_;
};

#endif

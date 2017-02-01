//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef HttpMessage_h
#define HttpMessage_h

#include <string>
#include <vector>
#include "http_header.h"

/*
From Apache HttpComponents:

HTTP messages use the generic message format of RFC 822 for
transferring entities (the payload of the message). Both 
types of message consist of a start-line, zero or more header
fields (also known as "headers"), an empty line (i.e., a line 
with nothing preceding the CRLF) indicating the end of the 
header fields, and possibly a message-body.

      generic-message = start-line
                        *(message-header CRLF)
                        CRLF
                        [ message-body ]
      start-line      = Request-Line | Status-Line
*/

const std::string HEADER_DELIMITER = "\r\n";
const std::string REQUEST_DELIMITER = "\r\n\r\n";

class HttpMessage {
public:
  HttpMessage(std::string start_line);
  virtual std::string Serialize();
  void AddHeader(HttpHeader header);
  void SetBody(std::string body);
  std::string GetBody();
private:
  std::string start_line_;
  std::string body_;
  std::vector<HttpHeader> headers_;  
};

#endif

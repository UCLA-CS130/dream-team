//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef HttpMessage_h
#define HttpMessage_h

#include <string>
#include <vector>

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
class HttpMessage {
public:
  HttpMessage(std::string start_line);
  void addHeader(std::string header);
  std::vector<std::string> getHeaders();
  std::string getBody();
private:
  std::string start_line_;
  std::vector<std::string> headers_;
};

#endif

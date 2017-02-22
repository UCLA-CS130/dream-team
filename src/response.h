//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef response_h
#define response_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>


// Represents an HTTP response.
//
// Usage:
//   Response r;
//   r.SetStatus(RESPONSE_200);
//   r.SetBody(...);
//   return r.ToString();
//
// Constructed by the RequestHandler, after which the server should call ToString
// to serialize.

const std::string HEADER_DELIMITER = "\r\n";
const std::string BODY_DELIMITER = "\r\n";
const std::string RESPONSE_DELIMITER = "\r\n\r\n";
const std::string HEADER_KEY_VALUE_DELIMITER = ": ";
const std::string VERSION = "HTTP/1.1";
const std::string STATUS_LINE_DELIMITER = " ";

class Response {
public:
  using Headers = std::vector<std::pair<std::string, std::string>>;
  enum ResponseCode {
    OK = 200,
    MOVED_PERMANENTLY = 301,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    SERVER_ERROR = 500
  };
  
  void SetStatus(const ResponseCode response_code);
  void AddHeader(const std::string& header_name, const std::string& header_value);
  void SetBody(const std::string& body);
  
  
  std::string ToString();
  std::string serializeResponseCode();
  
private:
  ResponseCode response_code_;
  Headers headers_;
  std::string body_;
};
#endif

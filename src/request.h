//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#ifndef request_h
#define request_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

// For the Request and Response classes, you need to implement the methods
// and add private data as appropriate. You may also need to modify or extend
// the API when implementing the reverse proxy. Use your good judgment.

// Represents an HTTP Request.
//
// Usage:
//   auto request = Request::Parse(raw_request);

const std::string HEADER_DELIMITER = "\r\n";
const std::string HEADER_KEY_VALUE_DELIMITER = ": ";

class Request {
public:
  using Headers = std::vector<std::pair<std::string, std::string>>;
  Request(std::string raw_request, std::string method, std::string uri, std::string version, Headers headers, std::string body);
  static std::unique_ptr<Request> Parse(const std::string& raw_request);
  
  std::string raw_request() const;
  std::string method() const;
  std::string uri() const;
  std::string version() const;
  
  Headers headers() const;
  
  std::string body() const;
private:
  std::string raw_request_;
  std::string method_;
  std::string uri_;
  std::string version_;
  
  Headers headers_;
  
  std::string body_;
};

#endif /* request_h */

//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#ifndef request_h
#define request_h

#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "http_consts.h"

// For the Request and Response classes, you need to implement the methods
// and add private data as appropriate. You may also need to modify or extend
// the API when implementing the reverse proxy. Use your good judgment.

// Represents an HTTP Request.
//
// Usage:
//   auto request = Request::Parse(raw_request);

class Request {
public:  
  static std::unique_ptr<Request> Parse(const std::string& raw_request);
  
  std::string raw_request() const;
  std::string method() const;
  std::string uri() const;
  std::string version() const;

  using Headers = std::vector<std::pair<std::string, std::string>>;  
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

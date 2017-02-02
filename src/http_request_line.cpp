//
//  HttpRequestLine.cpp
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#include "http_request_line.h"

HttpRequestLine::HttpRequestLine(std::string method, std::string uri, std::string version) {
  method_ = method;
  uri_ = uri;
  version_ = version;
}

std::string HttpRequestLine::GetMethod() {
  return method_;
}

std::string HttpRequestLine::GetProtocolVersion() {
  return version_;
}

std::string HttpRequestLine::GetUri() {
  return uri_;
}

std::string HttpRequestLine::Serialize() const {
  return method_ + " "  + uri_ + " " + version_;
}

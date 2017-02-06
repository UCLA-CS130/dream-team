//
//  HttpRequestLine.cpp
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#include <map>
#include "http_request_line.h"

std::map<std::string, std::string> content_mapper =
  {{"html", "text/html"},
   {"jpg", "image/jpeg"},
   {"png", "image/png"},
   {"gif", "image/gif"},
   {"htm", "text/html"}};

HttpRequestLine::HttpRequestLine(std::string method, std::string uri, std::string version) {
  method_ = method;
  uri_ = uri;
  version_ = version;
}

std::string HttpRequestLine::GetMethod() const {
  return method_;
}

std::string HttpRequestLine::GetProtocolVersion() const {
  return version_;
}

std::string HttpRequestLine::GetUri() const {
  return uri_;
}

std::string HttpRequestLine::GetContentType() const {
  std::string extension = uri_.substr(uri_.find_last_of(".") + 1);
  std::map<std::string, std::string>::iterator matches = content_mapper.find(extension);
  if(matches == content_mapper.end()) {
    return "text/plain";
  } 
  
  return matches->first;  
}

std::string HttpRequestLine::Serialize() const {
  return method_ + " "  + uri_ + " " + version_;
}

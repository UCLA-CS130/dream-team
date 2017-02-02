//
//  HttpRequestLine.cpp
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#include "http_request_line.h"

HttpRequestLine::HttpRequestLine(std::string method, std::string uri, std::string version) {
  m_method = method;
  m_uri = uri;
  m_version = version;
}

std::string HttpRequestLine::getMethod(){
  return m_method;
}

std::string HttpRequestLine::getProtocolVersion(){
  return m_version;
}

std::string HttpRequestLine::getUri(){
  return m_uri;
}

std::string HttpRequestLine::Serialize() const{
  return m_method + " "  + m_uri + " " + m_version;
}

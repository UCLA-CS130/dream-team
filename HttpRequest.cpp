//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "HttpRequest.h"


// only utilizes the status line of the HTTP request
HttpRequest::HttpRequest(std::string rawMessage) : m_request(rawMessage), m_method(""), m_body(""), m_protocol(""), m_port(0), m_path("") {
  // set default values, if the constructor is not called
  std::vector<std::string> tokens;
  tokenize(rawMessage, tokens, "\r\n");
  
  // request/status line
  std::string requestLine;
  if (tokens.size() > 0) {
    // tokens[0] is the request line
    HttpRequestLine m_requestLine(tokens[0]);
  } else {
    throw;
  }
  
  // Body stored in tokens[2]
  HttpRequestLine m_requestLine(tokens[2]);
  
  // Headers stored in tokens[1]
  std::string headers = tokens[1];
  tokens.clear();
  tokenize(headers, tokens);

}

std::string HttpRequest::getRequest(){
  return m_request;
}

std::string HttpRequest::getProtocol(){
  return m_protocol;
}

std::string HttpRequest::getMethod(){
  return m_method;
}

std::string HttpRequest::getPath(){
  return m_path;
}

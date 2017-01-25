//
//  codeForce practice
//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "HttpRequest.h"
#include "Utils.h"

// only utilizes the status line of the HTTP request
HttpRequest::HttpRequest(std::string rawMessage) : m_request(rawMessage), m_method(""), m_body(""), m_protocol(""), m_port(0), m_path("") {
  // set default values, if the constructor is not called
  std::vector<std::string> tokens;
  tokenize(rawMessage, tokens, "\r\n");
  
  // status line
  /*std::string requestLine;
  if (tokens.size() > 0) {
    requestLine = tokens[0];
  } else {
    throw;
  }
  
  // Headers stored in tokens[1]
  // Body stored in tokens[2]
  tokens.clear();
  
  tokenize(requestLine, tokens);
  if (tokens.size() == 3) {
    m_method = tokens[0];
    std::string path = tokens[1];
    if (path.length() > 0 && path[0] == '/') {   // check if the resource we are getting is properly formatted
      m_path = path;
    } else {
      throw;
    }
    
    m_protocol = tokens[2];
  } else {
    throw;
  }*/
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

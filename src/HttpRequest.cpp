//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "HttpRequest.h"


// only utilizes the status line of the HTTP request
HttpRequest::HttpRequest(std::string rawMessage) {
  // set default values, if the constructor is not called
  std::vector<std::string> tokens;
  tokenize(rawMessage, tokens, "\r\n");
  
  // request/status line
  if (tokens.size() > 0) {
    // tokens[0] is the request line
    m_requestLine = new HttpRequestLine(tokens[0]);
  } else {
    throw;
  }
  
  // Body stored in tokens[2]
  m_requestBody = new HttpRequestBody(tokens[2]);
  
  // Headers stored in tokens[1]
  std::string headers = tokens[1];
  tokens.clear();
  tokenize(headers, tokens);
  m_requestHeader = new HttpRequestHeader(tokens);
}

std::string HttpRequest::getRequest(){
  return m_request;
}

HttpRequestLine* HttpRequest::getRequestLine(){
  return m_requestLine;
}

HttpRequestHeader* HttpRequest::getRequestHeader(){
  return m_requestHeader;
}

HttpRequestBody* HttpRequest::getRequestBody(){
  return m_requestBody;
}

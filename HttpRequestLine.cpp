//
//  HttpRequestLine.cpp
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#include "HttpRequestLine.h"

HttpRequestLine::HttpRequestLine(std::string requestLine) : m_requestLine = requestLine{
  std::vector<std::string> tokens;
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
  }
}

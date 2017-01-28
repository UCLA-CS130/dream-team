//
//  HttpRequestLine.h
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#ifndef HttpRequestLine_h
#define HttpRequestLine_h
#include "Utils.h"
#include <stdio.h>
#include <string>
#include <vector>

#define GET "GET"
#define POST "POST"

class HttpRequestLine{
public:
  std::string getRequestLine();
  std::string getMethod();
  std::string getProtocol();
  std::string getPath();
private:
  std::string m_requestLine;
  std::string m_method;
  std::string m_path;
  std::string m_protocol
}

#endif /* HttpRequestLine_h */

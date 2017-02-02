//
//  HttpRequestLine.h
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#ifndef HttpRequestLine_h
#define HttpRequestLine_h
#include <stdio.h>
#include <string>
#include <vector>
#include "utils.h"

#define GET "GET"
#define POST "POST"

class HttpRequestLine{
public:
  HttpRequestLine(std::string method, std::string uri, std::string version);
  std::string getMethod();
  std::string getProtocolVersion();
  std::string getUri();
  std::string Serialize() const;
private:
  std::string m_method;
  std::string m_version;
  std::string m_uri;
};

#endif /* HttpRequestLine_h */

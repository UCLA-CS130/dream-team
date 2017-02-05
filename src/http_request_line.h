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

#define GET "GET"
#define POST "POST"

class HttpRequestLine {
public:
  HttpRequestLine(std::string method, std::string uri, std::string version);
  std::string GetMethod() const;
  std::string GetUri() const;
  std::string GetProtocolVersion() const;
  std::string Serialize() const;
private:
  std::string method_;
  std::string uri_;
  std::string version_;
};

#endif /* HttpRequestLine_h */

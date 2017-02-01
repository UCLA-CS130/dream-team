//
//  HttpRequestHeader.h
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#ifndef HttpRequestHeader_h
#define HttpRequestHeader_h
#include <string>
#include <vector>
#include <utility>
#include "utils.h"

class HttpRequestHeader{
public:
  HttpRequestHeader(std::vector<std::string> requestHeader);
  std::string findHeader(std::string header); // returns "" if header is not found
private:
  std::vector<std::pair<std::string, std::string> > m_requestHeader;
};

#endif /* HttpRequestHeader_h */

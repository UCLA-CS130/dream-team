//
//  HttpRequestHeader.h
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#ifndef HttpRequestHeader_h
#define HttpRequestHeader_h
#include "Utils.h"

class HttpRequestHeader{
public:
  std::vector<std::string> getRequestHeader();
private:
  std::vector<std::string> m_requestHeader;
};

#endif /* HttpRequestHeader_h */

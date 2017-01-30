//
//  HttpRequestBody.h
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#ifndef HttpRequestBody_h
#define HttpRequestBody_h
#include <string>

class HttpRequestBody{
public:
  HttpRequestBody(std::string requestBody);
  std::string getRequestBody();
private:
  std::string m_requestBody;
};

#endif /* HttpRequestBody_h */

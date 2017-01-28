//
//  HttpRequestBody.h
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#ifndef HttpRequestBody_h
#define HttpRequestBody_h

class HttpRequestBody{
public:
  HttpRequestBody(std::string requestBody);
private:
  std::string m_requestBody;

};

#endif /* HttpRequestBody_h */

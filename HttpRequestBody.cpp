//
//  HttpRequestBody.cpp
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#include "HttpRequestBody.h"

HttpRequestBody::HttpRequestBody(std::string requestBody)
: m_requestBody = requestBody{
  
}

std::string getRequestBody(){
  m_requestBody;
}

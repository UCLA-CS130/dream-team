//
//  HttpRequestHeader.cpp
//  
//
//  Created by Brian Cho on 1/27/17.
//
//

#include "http_request_header.h"

HttpRequestHeader::HttpRequestHeader(std::vector<std::string> requestHeader){
  int length = requestHeader.size();
  for(int i = 0; i < length; i++){
    if(i < length - 1)
      m_requestHeader.push_back(make_pair(requestHeader[i], requestHeader[i + 1]));
  }
}

std::string HttpRequestHeader::findHeader(std::string header){
  int length = m_requestHeader.size();
  for(int i = 0; i < length; i++){
    if(m_requestHeader[i].first == header)
      return m_requestHeader[i].second;
  }
  return "";
}


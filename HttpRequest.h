//
//  codeForce practice
//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#ifndef HttpRequest_h
#define HttpRequest_h
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

// currently only method, request, protocol and path are set
// class not needed for project 2
class HttpRequest{
public:
  HttpRequest(std::string request);
  std::string getRequest();
  std::vector<std::string> getHeaders();
  std::string getBody();
  std::string getProtocol();
  std::string getPort();
  std::string getPath();
  std::string getMethod();
private:
  std::string m_request;
  std::vector<std::string> m_header;
  std::string m_method;
  std::string m_body;
  std::string m_protocol;
  std::string m_port;
  std::string m_path;
};

#endif /* HttpRequest_h */

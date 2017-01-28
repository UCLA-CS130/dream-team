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
#include "Utils.h"
#include "HttpRequestLine.h"
#include "HttpRequestHeader.h"
#include "HttpRequestBody.h"

// currently only method, request, protocol and path are set
// class not needed for project 2
class HttpRequest{
public:
  HttpRequest(std::string request);
  std::string getRequest();
  HttpRequestLine getRequestLine();
  HttpRequestHeader getRequestHeader();
  HttpRequestBody getRequestBody();
  std::string getPort();

private:
  std::string m_request;
  HttpRequestLine m_requestLine;
  HttpRequestHeader m_requestHeader;
  HttpRequestBody m_requestBody;
  std::string m_port;
};

#endif /* HttpRequest_h */

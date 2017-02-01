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
#include "utils.h"
#include "http_request_line.h"
#include "http_request_header.h"
#include "http_request_body.h"

class HttpRequest{
public:
  HttpRequest(std::string rawMessage);
  std::string getRequest();
  HttpRequestLine* getRequestLine();
  HttpRequestHeader* getRequestHeader();
  HttpRequestBody* getRequestBody();

private:
  std::string m_request;
  HttpRequestLine* m_requestLine;
  HttpRequestHeader* m_requestHeader;
  HttpRequestBody* m_requestBody;
};

#endif /* HttpRequest_h */

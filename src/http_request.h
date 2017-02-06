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
#include "http_message.h"
#include "http_request_line.h"

class HttpRequest : public HttpMessage {
public:
  HttpRequest(HttpRequestLine request);
  HttpRequestLine GetRequestLine() const;
private:
  HttpRequestLine request_line_;
};

#endif /* HttpRequest_h */

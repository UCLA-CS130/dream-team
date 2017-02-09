//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef HttpResponse_h
#define HttpResponse_h

#include "http_message.h"
#include "status_line.h"

class HttpResponse : public HttpMessage {
 public:
  HttpResponse(StatusLine status);
  StatusLine GetStatusLine();
 private:
  StatusLine status_;
};

#endif

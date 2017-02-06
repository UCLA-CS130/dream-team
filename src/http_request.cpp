//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "http_request.h"

HttpRequest::HttpRequest(HttpRequestLine request)
  : HttpMessage(request.Serialize()), request_line_(request) {
}

HttpRequestLine HttpRequest::GetRequestLine() const {
  return request_line_;
}

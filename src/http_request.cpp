//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "http_request.h"

HttpRequest::HttpRequest(const HttpRequestLine &request)
  : HttpMessage(request.Serialize()), request_(request) {
}

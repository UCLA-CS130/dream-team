//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "http_response.h"

HttpResponse::HttpResponse(const StatusLine &status) 
  : HttpMessage(status.Serialize()), status_(status) {
}

//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "HttpResponse.h"

HttpResponse::HttpResponse(const StatusLine &status) 
  : HttpMessage(status.Serialize()), status_(status) {
}

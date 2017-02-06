//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "http_entity.h"

HttpEntity::HttpEntity() {}

HttpEntity::HttpEntity(std::string uri) : uri_(uri) {}

std::string HttpEntity::GetUri() { return uri_; }

bool HttpEntity::OpenStream(std::ifstream* out_stream) const {
  out_stream->open(uri_);
  return out_stream->good();
}

//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "request.h"
#include "utils.h"

std::unique_ptr<Request> Request::Parse(const std::string& raw_request) {
  std::string method;
  std::string uri;
  std::string version;

  std::vector<std::string> tokens;
  std::vector<std::string> request_line_tokens;
  std::string request_line_message;

  tokenize(raw_request, tokens, HEADER_DELIMITER);

  if (tokens.size() > 0) {
    request_line_message = tokens[0];
  }

  // request line
  tokenize(request_line_message, request_line_tokens);
  if (request_line_tokens.size() == 3) {
    method = request_line_tokens[0];
    uri = request_line_tokens[1];
    version = request_line_tokens[2];
  }

  Headers headers;
  std::string body;
  bool isHeader = true;
  for (unsigned i = 1; i < tokens.size(); i++) {
    if (isHeader && tokens[i] == "") {
      isHeader = false;
      continue;
    }

    if (isHeader) {
      std::vector<std::string> header_token;
      tokenize(tokens[i], header_token, HEADER_KEY_VALUE_DELIMITER);

      if (header_token.size() >= 1) {
        headers.push_back(make_pair(header_token[0], header_token[1]));
      }
    } else {
      body = tokens[i];
    }
  }
  
  Request* req = new Request();
  req->raw_request_ = raw_request;
  req->method_ = method;
  req->uri_ = uri;
  req->version_ = version;
  req->headers_ = headers;
  req->body_ = body;

  std::unique_ptr<Request> req_ptr(req);      
  return req_ptr;
}

std::string Request::raw_request() const { return raw_request_; }

std::string Request::method() const { return method_; }

std::string Request::uri() const { return uri_; }

std::string Request::version() const { return version_; }

Request::Headers Request::headers() const { return headers_; }

std::string Request::body() const { return body_; }

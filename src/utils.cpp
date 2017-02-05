//
//  Utils.cpp
//  codeForce practice
//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "utils.h"

// gets port number from config file
int NginxConfigGetPort(NginxConfig* config){
  for(const auto& statement : config->statements_){
    int rv = configStatmentRecur(statement.get());
    if(rv != -1)
      return rv;
  }
  return -1; // not found
}

// helper function to get port number from config file
int configStatmentRecur(NginxConfigStatement* statement){
  for (unsigned int i = 0; i < statement->tokens_.size(); i++) {
    if(statement->tokens_[i] == "listen" && i + 1 < statement->tokens_.size()){
      return std::stoi(statement->tokens_[i + 1]);
    }
  }
  
  if (statement->child_block_.get() != nullptr) {
    int rv = NginxConfigGetPort(statement->child_block_.get());
    if(rv != -1)
      return rv;
  }
  return -1; // default
}


void tokenize(const std::string &in, std::vector<std::string> &tokens,
              const std::string &delimeter) {
  const std::string str = in + delimeter; // Add on padding delimeter so we pick up the last item in our list
  size_t currStart = 0, lastFoundPosition = -1;
  while(currStart < str.length() &&
        lastFoundPosition + 1 < str.length() &&
        (lastFoundPosition = str.find(delimeter, lastFoundPosition + 1))
        != std::string::npos) {
    tokens.push_back(str.substr(currStart, lastFoundPosition - currStart));
    currStart = lastFoundPosition + delimeter.length();
  }
}


HttpRequest parse_message(std::string raw_message){
  std::string method;
  std::string uri;
  std::string version;
  std::vector<std::string> tokens;
  std::vector<std::string> request_line_tokens;
  std::string request_line_message;

  tokenize(raw_message, tokens, "\r\n");

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

  HttpRequestLine request_line(method, uri, version);
  HttpRequest request(request_line);  
  return request;
}

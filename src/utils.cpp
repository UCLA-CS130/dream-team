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


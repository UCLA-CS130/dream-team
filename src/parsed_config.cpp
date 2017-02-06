#include "parsed_config.h"
#include <iostream>

ParsedConfig::ParsedConfig(NginxConfig* config) 
  : port_number_(0), root_dir_("") { // Treating port 0 as invalid
	initParsedConfig(config);
}

bool ParsedConfig::initParsedConfig(NginxConfig* config) {
  for(const auto& statement : config->statements_) {
  	if (statement->child_block_.get() != nullptr && !initParsedConfig(statement->child_block_.get())) {
	    return false;
  	}

  	for (unsigned int i = 0; i < statement->tokens_.size(); i++) {
	    if (statement->tokens_[i] == "listen" && i + 1 < statement->tokens_.size()) {
	      	port_number_ = std::stoi(statement->tokens_[i + 1]);
	    } else if (statement->tokens_[i] == "root" && i + 1 < statement->tokens_.size()) {
	      	root_dir_ = statement->tokens_[i + 1];
	    }
  	}
  }

  return true;
}

unsigned ParsedConfig::GetPortNumber() {
  return port_number_;
}

std::string ParsedConfig::GetRootDirectory() {
  return root_dir_;
}
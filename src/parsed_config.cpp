#include "parsed_config.h"
#include <iostream>

ParsedConfig::ParsedConfig(NginxConfig* config) 
  : port_number_(INVALID_PORT), root_dir_("") { // Treating port 0 as invalid
	if (!initParsedConfig(config)) {
	  printf("port_number is: %d\n", port_number_);
	  std::cout << "root_dir_ is: " << root_dir_ << "\n";
	  throw std::invalid_argument("Bad config file");
	} else if (port_number_ > MAX_PORT) {
      throw std::invalid_argument("Bad port number");
	}
    /*if (!initialize(config)) {
	  printf("port_number is: %d\n", port_number_);
	  std::cout << "root_dir_ is: " << root_dir_ << "\n";
	  throw std::invalid_argument("Bad config file");
	} else if (port_number_ > MAX_PORT) {
      throw std::invalid_argument("Bad port number");
	}*/
}

/*bool ParsedConfig::initialize(NginxConfig* config) {
	for (int i = 0; i < config->statements_->tokens_.size(); i++) {
		if (config->statements_->tokens_[i] == "listen") {
			port_number_ = config->statements_->tokens_[i+1];
		} else if (config->statements_->tokens_[i] == "root") {
			root_dir_ = config->statements_->tokens_[i+1];
		}
	}

	return (port_number_ != INVALID_PORT && root_dir_ != "");
}*/

bool ParsedConfig::initParsedConfig(NginxConfig* config) {
  for(const auto& statement : config->statements_) {
  	std::cout << "initCall\n" << statement->ToString(0) << "\n";
  	//std::cout << "numtokens: " << statement.get()->tokens_.size() << "\n";
/*    if (!initParsedConfigHelper(statement.get()))
      return false;*/
  	/*for (const auto token : statement->tokens_) {
  		std::cout << token << "\n";
  	}*/
  	if (statement->child_block_.get() != nullptr && !initParsedConfig(statement->child_block_.get())) {
	  	std::cout << "Going into child block" << "\n";
	    return false;
  	}
  }

  return true;
}

bool ParsedConfig::initParsedConfigHelper(NginxConfigStatement* statement) {
  for (unsigned int i = 0; i < statement->tokens_.size(); i++) {
  	std::cout << statement->ToString(0) << "\n";
    if (statement->tokens_[i] == "listen" && i + 1 < statement->tokens_.size()) {
      port_number_ = std::stoi(statement->tokens_[i + 1]);
    } else if (statement->tokens_[i] == "root" && i + 1 < statement->tokens_.size()) {
      root_dir_ = statement->tokens_[i + 1];
    }
  }

  return (port_number_ != INVALID_PORT && root_dir_ != "");
}

/*bool ParsedConfig::initParsedConfig(NginxConfig* config) {
  for(const auto& statement : config->statements_) {
  	std::cout << "initCall\n" << statement->ToString(0) << "\n";
    if (!initParsedConfigHelper(statement.get()))
      return false;
  }

  return true;
}*/

// helper function to get port number from config file
/*bool ParsedConfig::initParsedConfigHelper(NginxConfigStatement* statement) {
  for (unsigned int i = 0; i < statement->tokens_.size(); i++) {
  	std::cout << "helperCall\n" << statement->ToString(0) << "\n";
    if (statement->tokens_[i] == "listen" && i + 1 < statement->tokens_.size()) {
      port_number_ = std::stoi(statement->tokens_[i + 1]);
    } else if (statement->tokens_[i] == "root" && i + 1 < statement->tokens_.size()) {
      root_dir_ = statement->tokens_[i + 1];
    }
  }
  
  if (statement->child_block_.get() != nullptr && !initParsedConfig(statement->child_block_.get())) {
    return false;
  }

  return (port_number_ != INVALID_PORT && root_dir_ != "");
}*/

unsigned ParsedConfig::getPortNumber() {
  return port_number_;
}

std::string ParsedConfig::getRootDirectory() {
  return root_dir_;
}
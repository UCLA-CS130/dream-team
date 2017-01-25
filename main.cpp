#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "nginx-configparser/config_parser.h"
#include "ConnectionManager.h"

int NginxConfigGetPort(NginxConfig* config);

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

int NginxConfigGetPort(NginxConfig* config){
  for(const auto& statement : config->statements_){
    int rv = configStatmentRecur(statement.get());
    if(rv != -1)
      return rv;
  }
  return -1; // not found
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: webserver <nginx_config_file>\n";
    return 1;
  }

  NginxConfigParser config_parser;
  NginxConfig config;
  config_parser.Parse(argv[1], &config);
  
  int port_number = NginxConfigGetPort(&config); // assign this value based on the config file

  try {
    ConnectionManager manager(port_number);
    manager.RunTcpServer();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

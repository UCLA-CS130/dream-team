#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "connection_manager.h"
#include "basic_server_config.h"

#define INVALID_PORT 0
#define MAX_PORT 65535

bool isParsedConfigValid(BasicServerConfig* pc) {
  // Echo is an optional parameter
  std::string echo_path = pc->GetEchoPath();
  std::cout << "Echo path is " << echo_path << std::endl;
  
  // treating 0 as invalid for now, as method returns unsigned
  int port_number = pc->GetPortNumber();
  if (port_number <= 0 || port_number > MAX_PORT) { 
    std::cerr << "Invalid port number" << std::endl;
    return false;
  }
  
  std::cout << "Server port number is " << port_number << std::endl;
  
  std::string root_url = pc->MapUserToHostUrl("/");
  if (root_url == "") {
    std::cerr << "Must provide at least one root url" << std::endl;
    return false;
  }
  
  std::cout << "Server's root url is " << root_url << std::endl;   
  return true;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: webserver <nginx_config_file>\n";
    return 1;
  }
  
  NginxConfigParser config_parser;
  NginxConfig config;
  if (!config_parser.Parse(argv[1], &config)) {
    std::cerr << "Invalid config file" << std::endl;
    return 1;
  }

  BasicServerConfig parsed_config(&config);
  if (!parsed_config.Init() || !isParsedConfigValid(&parsed_config)) {
    return 1;
  }
  
  try {
    ConnectionManager manager(&parsed_config);
    manager.RunTcpServer();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

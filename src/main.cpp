#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "connection_manager.h"
#include "parsed_config.h"

bool isParsedConfigValid(ParsedConfig* pc) {
  int port_number = pc->GetPortNumber();
  if (port_number <= 0 || port_number > MAX_PORT) { // treating 0 as invalid for now, as method returns unsigned
    std::cerr << "Invalid port number" << std::endl;
    return false;
  }

  std::string root_dir = pc->GetRootDirectory();
  if (root_dir == "") {
    std::cerr << "Invalid root directory" << std::endl;
    return false;
  }

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

  ParsedConfig parsed_config(&config);
  if (!isParsedConfigValid(&parsed_config)) {
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

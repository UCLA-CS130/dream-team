#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "connection_manager.h"
#include "parsed_config.h"

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

  try {
    ParsedConfig parsed_config(&config);
    ConnectionManager manager(&parsed_config);
    manager.RunTcpServer();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

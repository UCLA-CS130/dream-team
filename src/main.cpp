#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "connection_manager.h"
#include "utils.h"

#define MAX_PORT 65535

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
  
  int port_number = NginxConfigGetPort(&config);
  if (port_number < 0 || port_number > MAX_PORT) {
    std::cerr << "Invalid port number" << std::endl;
    return 1;
  }

  try {
    ConnectionManager manager(port_number);
    manager.RunTcpServer();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}

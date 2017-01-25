#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "nginx-configparser/config_parser.h"
#include "ConnectionManager.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: webserver <nginx_config_file>\n";
    return 1;
  }

  /*NginxConfigParser config_parser;
  NginxConfig config;
  config_parser.Parse(argv[1], &config);*/

  int port_number = 2000; // assign this value based on the config file

  try {
    ConnectionManager manager(port_number);
    manager.RunTcpServer();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

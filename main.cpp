#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "ConnectionManager.h"
#include "Utils.h"

int NginxConfigGetPort(NginxConfig* config);


int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: webserver <nginx_config_file>\n";
    return 1;
  }
  NginxConfigParser config_parser;
  NginxConfig config;
  config_parser.Parse(argv[1], &config);
  
  int port_number = NginxConfigGetPort(&config); // assign this value based on the config file
  if(port_number == -1){
    std::cerr << "port number not specified\n";
  }

  try {
    ConnectionManager manager(port_number);
    manager.RunTcpServer();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

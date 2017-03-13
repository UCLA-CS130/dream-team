#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include <thread>
#include "ssl_connection_manager.h"
#include "basic_server_config.h"

#define INVALID_PORT 0
#define MAX_PORT 65535

bool IsParsedConfigValid(BasicServerConfig* pc) {
  if (pc->IsHTTPPortDeclared()) {
    int http_port_number = pc->GetHTTPPortNumber();
    if (http_port_number <= 0 || http_port_number > MAX_PORT) {
      std::cerr << "Invalid http port number" << std::endl;
      return false;
    }

    std::cout << "HTTP port number is " << http_port_number << std::endl;
  }

  if (pc->IsSSLPortDeclared()) {
    int ssl_port_number = pc->GetSSLPortNumber();
    if (ssl_port_number <= 0 || ssl_port_number > MAX_PORT) {
      std::cerr << "Invalid ssl port number" << std::endl;
      return false;
    }

    std::cout << "HTTPS port number is " << ssl_port_number << std::endl;
  }

  return true;
}

void thread_worker(ConnectionManager* cm) {
  cm->RunTcpServer();
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: webserver <nginx_config_file>" << std::endl;
    return 1;
  }

  NginxConfigParser config_parser;
  NginxConfig config;
  if (!config_parser.Parse(argv[1], &config)) {
    std::cerr << "Invalid config file syntax" << std::endl;
    return 1;
  }

  BasicServerConfig parsed_config(&config);
  parsed_config.RegisterTrafficMonitor(&TrafficMonitor::Get());
  if (!parsed_config.Init() || !IsParsedConfigValid(&parsed_config)) {
    std::cerr << "Invalid config file option values" << std::endl;
    return 1;
  }

  if (parsed_config.IsHTTPPortDeclared() && parsed_config.IsSSLPortDeclared()) {
    ConnectionManager HttpManager(&parsed_config, parsed_config.GetHTTPPortNumber());
    SSLConnectionManager HttpsManager(&parsed_config, parsed_config.GetSSLPortNumber());

    std::thread HttpThread(thread_worker, &HttpManager);
    std::thread HttpsThread(thread_worker, &HttpsManager);

    HttpThread.join();
    HttpsThread.join();
  } else if (parsed_config.IsHTTPPortDeclared()) {
    ConnectionManager HttpManager(&parsed_config, parsed_config.GetHTTPPortNumber());
    HttpManager.RunTcpServer();
  } else if (parsed_config.IsSSLPortDeclared()) {
    SSLConnectionManager HttpsManager(&parsed_config, parsed_config.GetSSLPortNumber());
    HttpsManager.RunTcpServer();
  } else {
    std::cerr << "No ports specified" << std::endl;
    return 1;
  }

  return 0;
}

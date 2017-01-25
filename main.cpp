#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "nginx-configparser/config_parser.h"

#define REQUEST_DELIMITER "\r\n\r\n"

int NginxConfigGetPort(NginxConfig* config);

// Inspired by https://github.com/egalli64/thisthread/blob/master/asio/tcpIpCs.cpp
void runTcpServer(int port_number) {
  boost::asio::io_service aios;
  boost::asio::ip::tcp::acceptor acceptor(aios, 
					  boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_number));

  while (true) {
    boost::asio::ip::tcp::socket socket(aios);
    acceptor.accept(socket);

    std::stringstream message_stream;
    boost::asio::streambuf buffer;
    boost::system::error_code error;
    size_t len = read_until(socket, buffer, REQUEST_DELIMITER, error);

    // TODO: format the response with a status line, content-type, etc.

    if (len) {
      message_stream.write(boost::asio::buffer_cast<const char *>(buffer.data()), len);
      boost::asio::write(socket, boost::asio::buffer(message_stream.str()));
    }
  }
}

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
  printf("%s", config.ToString().c_str());
  
  int port_number = NginxConfigGetPort(&config); // assign this value based on the config file

  try {
    runTcpServer(port_number);
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

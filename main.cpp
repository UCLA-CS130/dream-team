#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include "nginx-configparser/config_parser.h"

#define REQUEST_DELIMITER "\r\n\r\n"

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
    runTcpServer(port_number);
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

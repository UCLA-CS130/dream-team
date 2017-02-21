//
// Created by Michael Chen on 2/28/17.
// Copyright © 2017 Chen. All rights reserved.
//
//ProxyHandler code for generating new request and capturing response is modeled off of
//http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp03/http/client/sync_client.cpp

#include "proxy_handler.h"
#include "parsed_config.h"
#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "utils.h"
#include <boost/regex.hpp>


RequestHandler::Status ProxyHandler::Init(const std::string& uri_prefix,
					 const NginxConfig& config) {
  uri_prefix_ = uri_prefix;
  ParsedConfig parser;
  proxy_host_ = parser.GetStatementValue(&config, "host");
  if (proxy_host_.length() == 0) {
    return RequestHandler::INVALID_CONFIG;
  }
  
  proxy_port_ = parser.GetStatementValue(&config, "port");
  if (proxy_port_.length() == 0) {
    return RequestHandler::INVALID_CONFIG;
  }

  redirect_uri_ = "";
  return RequestHandler::OK;
}

RequestHandler::Status ProxyHandler::HandleRequest(const Request &request, 
						  Response *response) {
  try {
    std::cout << "Host: " << proxy_host_ << std::endl;
    std::cout << "Port: " << proxy_port_ << std::endl;
    std::string body_;

    boost::asio::io_service io_service;
    
    // Get a list of endpoints corresponding to the server name.
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(proxy_host_, proxy_port_, boost::asio::ip::resolver_query_base::numeric_service);
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    boost::system::error_code conn_error = boost::asio::error::host_not_found;
    boost::asio::ip::tcp::socket socket (io_service);

    while (conn_error && endpoint_iterator != end) {
      socket.close();
      socket.connect(*endpoint_iterator++, conn_error);
    }

    // Try each endpoint until we successfully establish a connection.

    // Form the rrequest. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    boost::asio::streambuf request_;
    std::ostream request_stream(&request_);
    std::string redirect_uri;
    std::string orig_uri = request.uri();
    if (uri_prefix_.size() == 1) {
      redirect_uri = orig_uri;
    }
    else {
      if (uri_prefix_.size() + 1 >= orig_uri.size())
        redirect_uri = "/";
      else 
        redirect_uri = orig_uri.substr(uri_prefix_.size());
    }

    if (!redirect_uri_.empty()) {
      redirect_uri = redirect_uri_;
    }
    //TODO: Change to "/"
    request_stream << "GET " + redirect_uri + " HTTP/1.0\r\n";
    request_stream << "Host: " << proxy_host_ << "\r\n";
    request_stream << "Accept: */*\r\n";
    request_stream << "Connection: close\r\n\r\n";

    // Send the request.
    boost::asio::write(socket, request_);

    // Read the response status line. The response streambuf will automatically
    // grow to accommodate the entire line. The growth may be limited by passing
    // a maximum size to the streambuf constructor.
    boost::asio::streambuf response_;
    boost::asio::read_until(socket, response_, "\r\n");

    // Check that response is OK.
    std::istream response_stream(&response_);
    std::string http_version;
    response_stream >> http_version;
    unsigned int status_code;
    response_stream >> status_code;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
      std::cout << "Invalid response\n";
      return RequestHandler::INVALID_CONFIG;
    }
    if (status_code != 200 && status_code != 302) {
      std::cout << "Response returned with status code " << status_code << "\n";
      return RequestHandler::INVALID_CONFIG;
    } else {
      response->SetStatus(Response::ResponseCode::OK);
    }

    // Read the response headers, which are terminated by a blank line.
    boost::asio::read_until(socket, response_, "\r\n\r\n");

    std::string header;
    size_t index;
    size_t cr;
    std::string new_host = "";
    std::vector<std::pair<std::string, std::string>> header_vector;
    while (std::getline(response_stream, header) && header != "\r") {
      index = header.find(':', 0);
      cr = header.find('\r', index);
      if (index != std::string::npos) {
        if (header.substr(0, index).compare("Location") || status_code != 302) {
        header_vector.push_back(std::make_pair(header.substr(0, index), header.substr(index+2, cr - (index + 2))));
        }
        else {
          new_host = header.substr(index+2, cr - (index + 2));
          
          if (!strncmp(new_host.c_str(), "http://", 7)) {
            new_host = new_host.substr(7);
          } else if (!strncmp(new_host.c_str(), "https://", 8)) {
            new_host = new_host.substr(8);
          }
          size_t first_slash = new_host.find("/");
          if (first_slash != std::string::npos) {
            new_host = new_host.substr(0, first_slash);
            redirect_uri_ = new_host.substr(first_slash);
          }
          
          proxy_host_ = new_host;
          
        }
      }
     
    }
    if (!new_host.empty())
    {
      return HandleRequest(request, response);
    }
    else {
      for (unsigned i = 0; i < header_vector.size(); i++) {
        response->AddHeader(header_vector[i].first, header_vector[i].second);
      }
    }
    std::cout << "\n";

    // Write whatever content we already have to output.
    if (response_.size() > 0) {
      std::ostringstream ss;
      ss << &response_;
      body_ += ss.str();
    }
    
    // Read until EOF, writing data to output as we go.
    boost::system::error_code error;
    while (boost::asio::read(socket, response_, boost::asio::transfer_at_least(1), error)) {
      std::ostringstream ss;
      ss << &response_;
      body_ += ss.str();
    }

    if (error != boost::asio::error::eof)
      throw boost::system::system_error(error);
    if (uri_prefix_.size() > 1) { 
      boost::regex r("src\\s*=\\s*\"((?!http)[^\"]*)\"");
      std::string fmt = "src=\"" + uri_prefix_ + "\\1\"";
      boost::regex r2("href\\s*=\\s*\"((?!http)[^\"]*)\"");
      std::string fmt2 = "href=\"" + uri_prefix_ + "\\1\"";
      std::string replaced  = boost::regex_replace(body_, r, fmt, boost::match_default | boost::format_sed);
      body_ = boost::regex_replace(replaced, r2, fmt2, boost::match_default | boost::format_sed);
//    std::cout << "HTML Replaced:\n" << body_ << std::endl;
    }
    response->SetBody(body_);
    std::string length;
    std::ostringstream temp;
    temp  <<  ((int) body_.size());
    length = temp.str();
    response->AddHeader("Content-Length", length);
  } catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << "\n";
  }

  return RequestHandler::OK;
}

// Represents the parent of all request handlers. Implementations should expect to
// be long lived and created at server constrution.

#ifndef RequestHandler_h
#define RequestHandler_h

#include "http_request.h"
#include "http_response.h"
#include "nginx-configparser/config_parser.h"

class RequestHandler {
 public:
  enum Status {
    OK = 0;
    // Define your status codes here.
  };
  
  // Initializes the handler. Returns a response code indicating success or
  // failure condition.
  // uri_prefix is the value in the config file that this handler will run for.
  // config is the contents of the child block for this handler ONLY.
  virtual Status Init(const std::string& uri_prefix,
                      const NginxConfig& config) = 0;

  // Handles an HTTP request, and generates a response. Returns a response code
  // indicating success or failure condition. If ResponseCode is not OK, the
  // contents of the response object are undefined, and the server will return
  // HTTP code 500.
  virtual Status HandleRequest(const Request& request,
                               Response* response) = 0;
};

#endif
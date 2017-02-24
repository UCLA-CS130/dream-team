// Represents the parent of all request handlers. Implementations should expect to
// be long lived and created at server constrution.

#ifndef RequestHandler_h
#define RequestHandler_h

#include <map>
#include <memory>
#include <string>
#include "request.h"
#include "response.h"
#include "nginx-configparser/config_parser.h"

class RequestHandler {
 public:
  enum Status {
    OK = 0,
    INVALID_CONFIG = 1,
    UNKNOWN_HANDLER = 2
  };
  
  static const std::string CONTENT_TYPE_HEADER;
  static const std::string TYPE_TEXT_PLAIN;
  
  static RequestHandler* CreateByName(const std::string& type);
  
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
 protected:
  std::string uri_prefix_; 
  void AttachTextPlainContentTypeHeader(Response* resp);
};

// Notes:
// * The trick here is that you can declare an object at file scope, but you
//   can't do anything else, such as set a map key. But you can get around this
//   by creating a class that does work in its constructor.
// * request_handler_builders must be a pointer. Otherwise, it won't necessarily
//   exist when the RequestHandlerRegisterer constructor gets called.

extern std::map<std::string, RequestHandler* (*)(void)>* request_handler_builders;
template<typename T>
class RequestHandlerRegisterer {
 public:
  RequestHandlerRegisterer(const std::string& type) {
    if (request_handler_builders == nullptr) {
      request_handler_builders = new std::map<std::string, RequestHandler* (*)(void)>;
    }
    
    (*request_handler_builders)[type] = RequestHandlerRegisterer::Create;
  }
  static RequestHandler* Create() {
    return new T;
  }
};

#define REGISTER_REQUEST_HANDLER(ClassName) \
  static RequestHandlerRegisterer<ClassName> ClassName##__registerer(#ClassName)

#endif

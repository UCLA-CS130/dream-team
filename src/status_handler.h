//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef StatusHandler_h
#define StatusHandler_h

#include <map>
#include "request_handler.h"

class StatusHandler : public RequestHandler {
 public:
  struct HandlerInfo {
    std::string prefix;
    std::string id;
  };

  virtual RequestHandler::Status Init(const std::string& uri_prefix,
				      const NginxConfig& config) override;
  
  virtual RequestHandler::Status HandleRequest(const Request& request,
					       Response* response) override;

  void UpdateStats(const Request& req, Response::ResponseCode resp_code);
  void UpdateRequestHandlers(const std::vector<HandlerInfo>& handler_paths);
 private:
  std::map<std::string, std::map<Response::ResponseCode, unsigned>>
    url_stat_tracker_;
  std::vector<StatusHandler::HandlerInfo> handler_paths_;
};

#endif

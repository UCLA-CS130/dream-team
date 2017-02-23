//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "status_handler.h"

RequestHandler::Status StatusHandler::Init(const std::string& uri_prefix,
					   const NginxConfig& config) {
  return RequestHandler::OK;
}
  
RequestHandler::Status StatusHandler::HandleRequest(const Request& request,
						    Response* response) {  
  std::string resp_body = "---Request Handlers---\n";
  for (StatusHandler::HandlerInfo path_info : handler_paths_) {
    resp_body += path_info.id + " " + path_info.prefix + "\n";
  }

  AttachTextPlainContentTypeHeader(response);
  response->SetStatus(Response::OK);
  response->SetBody(resp_body);
  return RequestHandler::OK;
}

void StatusHandler::UpdateStats(const Request& request,
				Response::ResponseCode resp_code) {
  std::string client_uri = request.uri();
  if (url_stat_tracker_.count(client_uri) == 0) {
    url_stat_tracker_[client_uri][resp_code] = 0;
  }

  if (url_stat_tracker_[client_uri].count(resp_code) == 0) {
    url_stat_tracker_[client_uri][resp_code] = 0;
  }

  url_stat_tracker_[client_uri][resp_code] += 1;  
}

void StatusHandler::UpdateRequestHandlers(const std::vector<StatusHandler::HandlerInfo>& handler_paths) {
  handler_paths_ = handler_paths;
}

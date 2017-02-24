//
// Created by Usama Riaz on 2/22/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "status_handler.h"
#include "traffic_monitor.h"

RequestHandler::Status StatusHandler::Init(const std::string& uri_prefix,
					   const NginxConfig& config) {
  return RequestHandler::OK;
}
  
RequestHandler::Status StatusHandler::HandleRequest(const Request& request,
						    Response* response) {  
  std::string resp_body = TrafficMonitor::Get().PrettyPrintStats();

  AttachTextPlainContentTypeHeader(response);
  response->SetStatus(Response::OK);
  response->SetBody(resp_body);
  return RequestHandler::OK;
}

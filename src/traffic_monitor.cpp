//
// Created by Usama Riaz on 2/23/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "traffic_monitor.h"

void TrafficMonitor::SetHandlerPaths(std::vector<TrafficMonitor::HandlerInfo> handler_paths) {
  handler_paths_ = handler_paths;
}

void TrafficMonitor::UpdateStats(const Request& request,
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

std::string TrafficMonitor::PrettyPrintStats() {
  std::string resp_body = "---Request Handlers---\n";
  for (TrafficMonitor::HandlerInfo path_info : handler_paths_) {
    resp_body += path_info.id + " " + path_info.prefix + "\n";
  }
  
  resp_body += "\n---Site Traffic---\n";
  for (auto const& uri_to_resp_map : url_stat_tracker_) {
    std::string uri = uri_to_resp_map.first;
    resp_body += uri + ": {";

    std::map<Response::ResponseCode, unsigned> url_info = uri_to_resp_map.second;
    for (auto const& resp_to_count : url_info) {
      resp_body += " " + std::to_string(resp_to_count.first) 
	+ ": " + std::to_string(resp_to_count.second);
    }
    
    resp_body += " }\n";
  }

  return resp_body;
}

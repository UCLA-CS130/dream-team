//
// Created by Usama Riaz on 2/23/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef TrafficMonitor_h
#define TrafficMonitor_h

#include <map>
#include <vector>
#include <string>
#include "request.h"
#include "response.h"

class TrafficMonitor {
 public:
  struct HandlerInfo {
    std::string prefix;
    std::string id;
  };
  
  static TrafficMonitor& Get() {
    static TrafficMonitor instance;
    return instance;
  }

  void SetHandlerPaths(std::vector<TrafficMonitor::HandlerInfo> handler_paths);
  void UpdateStats(const Request& req, Response::ResponseCode resp_code);
  std::string PrettyPrintStats();
 private:
  std::map<std::string, std::map<Response::ResponseCode, unsigned>>
    url_stat_tracker_;
  std::vector<TrafficMonitor::HandlerInfo> handler_paths_;
};

#endif

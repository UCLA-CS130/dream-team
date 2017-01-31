//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#ifndef ConnectionManager_h
#define ConnectionManager_h

#include <string>
#include <boost/asio.hpp>
#include "HttpResponse.h"

class ConnectionManager {
 public:
  ConnectionManager(unsigned port_number);
  void RunTcpServer();
 private:
  unsigned port_number_;
};

#endif

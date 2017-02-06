//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "basic_server_config.h"

const std::string SERVER_OBJ = "server";
const std::string LOCATION_OBJ = "location";
const std::string PORT_KEY = "listen";
const std::string ECHO_KEY = "echo";
const std::string ROOT_KEY = "root";

BasicServerConfig::BasicServerConfig(NginxConfig* config) : ParsedConfig(config) {}

bool BasicServerConfig::Init() {
  NginxConfig* root_config = GetConfig();
  std::vector<std::shared_ptr<NginxConfigStatement>> server_matches = 
    FilterStatements(root_config, SERVER_OBJ);
  
  if (server_matches.size() == 0) {
    return false;
  }
  
  std::shared_ptr<NginxConfigStatement> config_statement = server_matches[0];
  NginxConfig* server_block = config_statement->child_block_.get();
  
  bool init_status = 
    InitPortNumber(server_block) &&
    InitEchoPath(server_block) &&
    InitRootUrlPaths(server_block);

  return init_status;
}

bool BasicServerConfig::InitPortNumber(NginxConfig* config) {
  std::string port_num = GetStatementValue(config, PORT_KEY);
  if (port_num == "") {
    return false;
  }
  
  port_number_ = std::stoi(port_num);
  return true;
}

bool BasicServerConfig::InitEchoPath(NginxConfig* config) {
  echo_path_ = GetStatementValue(config, ECHO_KEY);
  return true;
}

bool BasicServerConfig::InitRootUrlPaths(NginxConfig* config) {
  std::vector<std::shared_ptr<NginxConfigStatement>> location_matches = 
    FilterStatements(config, LOCATION_OBJ);
  
  if (location_matches.size() == 0) {
    return false;
  }
  
  for (const auto& statement : location_matches) {
    if (statement->tokens_.size() >= 2) {
      NginxConfig* location_map_block = statement->child_block_.get();

      std::string user_url = statement->tokens_[1];
      std::string host_url = GetStatementValue(location_map_block, ROOT_KEY);
      
      root_url_paths_[user_url] = host_url;
    }    
  }
  
  return true;
}

unsigned BasicServerConfig::GetPortNumber() {
  return port_number_;
}

std::string BasicServerConfig::GetEchoPath() {
  return echo_path_;
}

std::string BasicServerConfig::MapUserToHostUrl(std::string user_url) {
  return root_url_paths_[user_url];
}

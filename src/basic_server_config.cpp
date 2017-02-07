//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "basic_server_config.h"
#include "utils.h"

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

bool BasicServerConfig::IsRequestEcho(std::string req) {
  std::string uri_start = GetUriStart(req);
  return uri_start == GetEchoPath();
}

unsigned GetNumberSlashes(std::string uri);

std::string BasicServerConfig::MapUserToHostUrl(std::string user_url) {
  std::vector<std::string> host_url_keys;
  for (auto const& map: root_url_paths_) {
    host_url_keys.push_back(map.first);
  }
  
  unsigned slashes = GetNumberSlashes(user_url);
  std::string uri_start = slashes == 1 ? "/" : GetUriStart(user_url); 

  for (std::string host_path : host_url_keys) {   
    if (host_path == uri_start) {
      std::string mapped_url = root_url_paths_[host_path];      
      user_url = user_url.replace(0, host_path.length(), mapped_url);
      break;
    }
  }

  return user_url;
}

unsigned GetNumberSlashes(std::string uri) {
  unsigned int slash_count = 0;  
  for (unsigned i = 0; i < uri.length() && slash_count < 2; i++) {
    if (uri[i] == '/') {
      slash_count++;
    }
  }
  
  return slash_count;
}

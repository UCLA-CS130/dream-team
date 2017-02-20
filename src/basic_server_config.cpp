//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "basic_server_config.h"
#include "utils.h"

const std::string PORT_KEY = "port";
const std::string LOCATION_OBJ = "path";
const std::string DEFAULT_OBJ = "default";
const std::string ROOT_KEY = "root";

const std::string ECHO_HANDLER_ID = "EchoHandler";
const std::string STATIC_HANDLER_ID = "StaticHandler";
const std::string NOT_FOUND_HANDLER_ID = "NotFoundHandler";

BasicServerConfig::BasicServerConfig(NginxConfig* config) : ParsedConfig(config) {}

bool BasicServerConfig::Init() {
  NginxConfig* root_config = GetConfig();
  bool init_status = 
    InitPortNumber(root_config) &&
    InitRequestHandlers(root_config);

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

bool BasicServerConfig::InitRequestHandlers(NginxConfig* config) {
  std::vector<std::shared_ptr<NginxConfigStatement>> location_matches = 
    FilterStatements(config, LOCATION_OBJ);
  
  for (const auto& statement : location_matches) {
    if (statement->tokens_.size() >= 3) {
      NginxConfig* location_map_block = statement->child_block_.get();

      std::string uri = statement->tokens_[1];
      std::string handler_id = statement->tokens_[2];
      std::string root_dir = GetStatementValue(location_map_block, ROOT_KEY);
      
      uri_to_request_handler_[uri] = BuildHandlerForUri(uri, handler_id, root_dir);
    }    
  }

  std::vector<std::shared_ptr<NginxConfigStatement>> default_matches =
    FilterStatements(config, DEFAULT_OBJ);

  for (const auto& statement : default_matches) {
    if (statement->tokens_.size() == 2) {
      std::string handler_id = statement->tokens_[1];
      default_handler_ = BuildHandlerForUri("", handler_id, "");
    }    
  }
  
  return true;
}

RequestHandler* GetRequestHandlerFromUri(std::string uri) {
  return uri_to_request_handler_[uri];
}

RequestHandler* BuildHandlerForUri(std::string uri, std::string handler_id, std::string root_dir) {
    /* TODO: Return the appropriate RequestHandler* */
    return nullptr;
}

unsigned BasicServerConfig::GetPortNumber() {
  return port_number_;
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

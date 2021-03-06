//
// Created by Usama Riaz on 1/24/17.
// Copyright © 2017 Riaz. All rights reserved.
//

#include "basic_server_config.h"
#include "utils.h"

#define PATH_NUM_TOKENS 3
#define DEFAULT_NUM_TOKENS 2
#define SSL_NUM_TOKENS 2

const std::string PORT_KEY = "port";
const std::string SSL_PORT_KEY = "ssl-port";
const std::string LOCATION_OBJ = "path";
const std::string DEFAULT_OBJ = "default";
const std::string ROOT_KEY = "root";
const std::string SSL_PRIVATE_PATH_KEY = "private_key_path";
const std::string SSL_PUBLIC_PATH_KEY = "public_key_path";

const std::string HANDLER_ECHO_ID = "EchoHandler";
const std::string HANDLER_STATIC_ID = "StaticHandler";
const std::string HANDLER_NOT_FOUND_ID = "NotFoundHandler";
const std::string HANDLER_STATUS_ID = "StatusHandler";

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
    http_port_declared_ = false;
  } else {
    http_port_number_ = std::stoi(port_num);
    http_port_declared_ = true;
  }

  std::vector<std::shared_ptr<NginxConfigStatement>> ssl_block_matches =
    FilterStatements(config, SSL_PORT_KEY);

  if (ssl_block_matches.size() == 0) {
    ssl_port_declared_ = false;
  } else {
    ssl_port_declared_ = true;

    std::shared_ptr<NginxConfigStatement> ssl_info = ssl_block_matches[0];

    if (ssl_info->tokens_.size() >= SSL_NUM_TOKENS) {
      NginxConfig* ssl_child_block = ssl_info->child_block_.get();
      ssl_port_number_ = std::stoi(ssl_info->tokens_[1]);
      ssl_public_key_path_ = GetStatementValue(ssl_child_block, SSL_PUBLIC_PATH_KEY);
      ssl_private_key_path_ = GetStatementValue(ssl_child_block, SSL_PRIVATE_PATH_KEY);
    }
  }

  if (!http_port_declared_ && !ssl_port_declared_) {
    return false;
  }

  return true;
}

bool BasicServerConfig::InitRequestHandlers(NginxConfig* config) {
  std::vector<TrafficMonitor::HandlerInfo> handler_descriptors;

  std::vector<std::shared_ptr<NginxConfigStatement>> location_matches =
    FilterStatements(config, LOCATION_OBJ);

  for (const auto& statement : location_matches) {
    if (statement->tokens_.size() >= PATH_NUM_TOKENS) {
      NginxConfig* path_child_block = statement->child_block_.get();
      std::string uri = statement->tokens_[1];
      std::string handler_id = statement->tokens_[2];

      uri_to_request_handler_[uri] = BuildHandlerForUri(uri, handler_id, path_child_block);

      TrafficMonitor::HandlerInfo h_info;
      h_info.prefix = uri;
      h_info.id = handler_id;
      handler_descriptors.push_back(h_info);
    }
  }

  std::vector<std::shared_ptr<NginxConfigStatement>> default_matches =
    FilterStatements(config, DEFAULT_OBJ);

  for (const auto& statement : default_matches) {
    if (statement->tokens_.size() == DEFAULT_NUM_TOKENS) {
      NginxConfig* default_child_block = statement->child_block_.get();
      std::string handler_id = statement->tokens_[1];
      default_handler_ = BuildHandlerForUri("", handler_id, default_child_block);

      TrafficMonitor::HandlerInfo h_info;
      h_info.prefix = "";
      h_info.id = handler_id;
      handler_descriptors.push_back(h_info);
    }
  }

  if (traffic_monitor_ != nullptr) {
    traffic_monitor_->SetHandlerPaths(handler_descriptors);
  }

  return true;
}

bool BasicServerConfig::IsHTTPPortDeclared() {
  return http_port_declared_;
}

bool BasicServerConfig::IsSSLPortDeclared() {
  return ssl_port_declared_;
}

void BasicServerConfig::RegisterTrafficMonitor(TrafficMonitor* monitor) {
  traffic_monitor_ = monitor;
}

std::string BasicServerConfig::GetLongestMatchingUri(std::string client_uri) {
  std::vector<std::string> host_url_keys;
  for (auto const& map: uri_to_request_handler_) {
    host_url_keys.push_back(map.first);
  }

  unsigned max_matches = 0;
  std::string max_matches_path = "";
  for (std::string host_path : host_url_keys) {
    // Count matches not including beginning slash
    unsigned matches = NumberMatches(host_path, client_uri) - 1;
    if (host_path == "/") {
      matches = 1;
    }

    if (matches > max_matches) {
      max_matches = matches;
      max_matches_path = host_path;
    }
  }

  return max_matches_path;
}


RequestHandler* BasicServerConfig::GetRequestHandlerFromUri(std::string uri) {
  std::string host_uri = GetLongestMatchingUri(uri);
  if (uri_to_request_handler_.count(host_uri) > 0) {
    return uri_to_request_handler_[host_uri].get();
  }

  return default_handler_.get();
}

std::unique_ptr<RequestHandler> BasicServerConfig::BuildHandlerForUri(std::string uri,
								      std::string handler_id,
								      NginxConfig* child_block) {
  RequestHandler* handler = RequestHandler::CreateByName(handler_id);
  if (handler != nullptr) {
    handler->Init(uri, *child_block);
  }

  return std::unique_ptr<RequestHandler>(handler);
}

void BasicServerConfig::UpdateStatusHandlers(const Request& req, const Response& resp) {
  if (traffic_monitor_ != nullptr) {
    traffic_monitor_->UpdateStats(req, resp.GetStatus());
  }
}

unsigned BasicServerConfig::GetHTTPPortNumber() {
  return http_port_number_;
}

unsigned BasicServerConfig::GetSSLPortNumber() {
  return ssl_port_number_;
}

std::string BasicServerConfig::GetSSLPrivateKeyPath() {
  return ssl_private_key_path_;
}

std::string BasicServerConfig::GetSSLPublicKeyPath() {
  return ssl_public_key_path_;
}

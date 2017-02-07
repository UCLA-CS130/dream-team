#include "parsed_config.h"
#include <iostream>

ParsedConfig::ParsedConfig(NginxConfig* config) : config_(config) {}

std::vector<std::shared_ptr<NginxConfigStatement>> ParsedConfig::FilterStatements(NginxConfig* root, 
									      std::string search_statement) {
  std::vector<std::shared_ptr<NginxConfigStatement>> matching_statements;
  for (const auto&  statement : root->statements_) {
    std::string statement_name = statement->tokens_[0];
    if (statement_name == search_statement) {
      std::shared_ptr<NginxConfigStatement> match(statement);
      matching_statements.push_back(match);
    }
  }

  return matching_statements;
}

std::vector<std::string> ParsedConfig::GetStatementValues(NginxConfig* root, const std::string search_statement) {
  std::vector<std::shared_ptr<NginxConfigStatement>> matches = FilterStatements(root, search_statement);
  std::vector<std::string> out;
  for (const auto& statement : matches) {
    std::vector<std::string> tokens = statement->tokens_;
    if (tokens.size() > 0) {
      out.push_back(tokens[tokens.size() - 1]);
    }
  }

  return out;
}

std::string ParsedConfig::GetStatementValue(NginxConfig* root, const std::string search_statement) {
  std::vector<std::string> matches = GetStatementValues(root, search_statement);
  if (matches.size() == 0) {
    return "";
  }

  return matches[0];
}

NginxConfig* ParsedConfig::GetConfig() {
  return config_;
}

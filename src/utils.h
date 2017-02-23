//
//  Utils.h
//  codeForce practice
//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#ifndef Utils_h
#define Utils_h

#include <string>
#include <vector>

// parses a string by delimeter
void tokenize(const std::string &in, std::vector<std::string> &tokens,
              const std::string &delimeter = " ");
std::string GetUriStart(std::string uri);

#endif /* Utils_h */

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

// Splits a string by delimiter and sends tokenized output to tokens
void tokenize(const std::string &in, std::vector<std::string> &tokens,
              const std::string &delimeter = " ");

unsigned NumberMatches(const std::string s1, const std::string s2);

#endif /* Utils_h */

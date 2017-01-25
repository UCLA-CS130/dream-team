//
//  Utils.cpp
//  codeForce practice
//
//  Created by Brian Cho on 1/22/17.
//  Copyright © 2017 Cho. All rights reserved.
//

#include "Utils.h"

void tokenize(const std::string &in, std::vector<std::string> &tokens, 
	      const std::string &delimeter) {
  const std::string str = in + delimeter; // Add on padding delimeter so we pick up the last item in our list
  size_t currStart = 0, lastFoundPosition = -1;
  while(currStart < str.length() &&
        lastFoundPosition + 1 < str.length() &&
        (lastFoundPosition = str.find(delimeter, lastFoundPosition + 1)) 
	!= std::string::npos) {
    tokens.push_back(str.substr(currStart, lastFoundPosition - currStart));
    currStart = lastFoundPosition + delimeter.length();
  }
}

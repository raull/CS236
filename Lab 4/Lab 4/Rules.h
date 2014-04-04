/*
 * Rules.h
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#ifndef RULES_H_
#define RULES_H_

#include <vector>
#include "Token.h"
#include <iostream>

class Rules {
public:
	Rules();
	virtual ~Rules();
	vector<Token *> valueList;

	std::string toString() const;
};

#endif /* RULES_H_ */

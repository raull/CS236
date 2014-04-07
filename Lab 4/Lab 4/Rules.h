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
#include "Tuple.h"
#include "Predicates.h"
#include <iostream>

class Rules {
public:
	Rules();
	virtual ~Rules();
	vector<Token *> valueList;
    
    Predicates headPredicate;
    vector<Predicates> predicateList;

	std::string toString() const;
};

#endif /* RULES_H_ */

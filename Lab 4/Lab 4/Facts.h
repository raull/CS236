/*
 * Facts.h
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#ifndef FACTS_H_
#define FACTS_H_

#include <vector>
#include "Token.h"
#include "Tuple.h"

class Facts {
public:
	Facts();
	virtual ~Facts();

	vector<Token *> valueList;

	std::string toString() const;
	Tuple getTuple();
	string getName();

};

#endif /* FACTS_H_ */

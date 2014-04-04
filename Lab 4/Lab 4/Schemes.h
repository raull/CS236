/*
 * Schemes.h
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#ifndef SCHEMES_H_
#define SCHEMES_H_

#include <vector>
#include "Token.h"
#include <iostream>
#include <set>

using namespace std;

class Schemes {
public:
	Schemes();
	virtual ~Schemes();
	vector<Token *> valueList;

	std::string toString() const;
	vector<Token> getSchema();
	string getName();
};



#endif /* SCHEMES_H_ */

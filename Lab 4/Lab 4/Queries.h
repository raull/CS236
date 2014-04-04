/*
 * Queries.h
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#ifndef QUERIES_H_
#define QUERIES_H_

#include <vector>
#include "Token.h"
#include "Tuple.h"

class Queries {
public:
	Queries();
    Queries(Tuple tuple, string name);
	virtual ~Queries();

	vector<Token *> valueList;
    string name;
    Tuple tuple;

	std::string toString() const;
	Tuple getTuple();
	string getName();
};

#endif /* QUERIES_H_ */

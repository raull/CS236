/*
 * Tuple.h
 *
 *  Created on: Mar 15, 2014
 *      Author: raull
 */

#ifndef TUPLE_H_
#define TUPLE_H_

#include <set>
#include <vector>
#include "Token.h"

using namespace std;

class Tuple {

public:

	//Instance Variables
	vector<Token> elements;

	//Constructor and Destructor
	Tuple();
	Tuple(vector<Token> list);
	virtual ~Tuple();

	//Instance Methods
	Token getElementAtIndex(int index);
	string toString();
	bool operator<(const Tuple& tuple) const;
};


#endif /* TUPLE_H_ */

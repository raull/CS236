/*
 * Predicates.h
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#ifndef PREDICATES_H_
#define PREDICATES_H_

#include "Tuple.h"

class Predicates {
public:
	Predicates();
	virtual ~Predicates();
    
    Tuple tuple;
    string name;
};

#endif /* PREDICATES_H_ */

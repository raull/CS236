/*
 * Rules.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#include "Rules.h"
#include "Tuple.h"
#include <sstream>

Rules::Rules() {
	// TODO Auto-generated constructor stub

}

Rules::~Rules() {
	// TODO Auto-generated destructor stub
}

string Rules::toString() const{
	stringstream result;
    
	result << "Head Predicate " <<headPredicate.name << headPredicate.toString() << "\n";
    
    result << "List of Predicates\n";
    for (int i=0; i<predicateList.size(); i++) {
        result << predicateList[i].name  << predicateList[i].toString() << "\n";
    }
    
	return result.str();

}


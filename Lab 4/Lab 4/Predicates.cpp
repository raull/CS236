/*
 * Predicates.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#include "Predicates.h"
#include <sstream>


Predicates::Predicates() {
	// TODO Auto-generated constructor stub
    this->name = "";
}

Predicates::~Predicates() {
	// TODO Auto-generated destructor stub
}

string Predicates::toString() const{
    stringstream result;
    
	result << "(";
    
	for(int i=0; i<tuple.elements.size(); i++){
		if(i != tuple.elements.size() - 1)
			result << tuple.elements[i].getTokensValue() << ", ";
		else
			result << tuple.elements[i].getTokensValue() << ")";
	}
    
	return result.str();
}

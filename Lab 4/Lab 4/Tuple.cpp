/*
 * Tuple.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: raull
 */

#include "Tuple.h"
#include <sstream>

Tuple::Tuple() {
	// TODO Auto-generated constructor stub
}

Tuple::Tuple(vector<Token> list){
	elements = list;
}

Tuple::~Tuple() {
	// TODO Auto-generated destructor stub
}

Token Tuple::getElementAtIndex(int index){
	return elements[index];
}

string Tuple::toString(){

	stringstream result;

	result << "(";

	for(int i=0; i<elements.size(); i++){
		if(i != elements.size() - 1)
			result << elements[i].getTokensValue() << ", ";
		else
			result << elements[i].getTokensValue() << ")";
	}

	return result.str();
}


bool Tuple::operator<(const Tuple& tuple) const{
	return elements < tuple.elements;
}

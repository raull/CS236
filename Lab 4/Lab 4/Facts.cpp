/*
 * Facts.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#include "Facts.h"
#include "TokenType.h"

Facts::Facts() {
	// TODO Auto-generated constructor stub

}

Facts::~Facts() {
	// TODO Auto-generated destructor stub
}

string Facts::toString() const{
	string result = "";
	for(int i=0; i<valueList.size(); i++){
		Token *tmp = valueList[i];
		result += tmp->getTokensValue();
		//cout << "The result is currently: " + result + "\n";
	}
	return result;
}

string Facts::getName(){
	Token nameToken = *valueList[0];
	return nameToken.getTokensValue();
}

Tuple Facts::getTuple(){
	vector<Token> newTuple;
	for(int i=0; i<valueList.size(); i++){
		Token tempToken = *valueList[i];
		if((tempToken.getTokenType() == ID || tempToken.getTokenType() == STRING) && i != 0){
			newTuple.push_back(tempToken);
		}
	}
	return *(new Tuple(newTuple));
}

/*
 * Schemes.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#include "Schemes.h"
#include "TokenType.h"

Schemes::Schemes() {
	// TODO Auto-generated constructor stub

}

Schemes::~Schemes() {
	// TODO Auto-generated destructor stub
}

string Schemes::toString() const{
	string result = "";
	for(int i=0; i<valueList.size(); i++){
		Token *tmp = valueList[i];
		result += tmp->getTokensValue();
		//cout << "The result is currently: " + result + "\n";
	}
	return result;
}

vector<Token> Schemes::getSchema(){

	vector<Token> newSet;
	for(int i=0; i<valueList.size(); i++){
		Token tempToken = *valueList[i];
		if((tempToken.getTokenType() == ID || tempToken.getTokenType() == STRING) && tempToken.getTokensValue().compare(this->getName())){
			newSet.push_back(tempToken);
		}
	}

	return newSet;
}

string Schemes::getName(){
	Token tokenName = *valueList[0];
	return tokenName.getTokensValue();
}

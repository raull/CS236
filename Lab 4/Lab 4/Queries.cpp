/*
 * Queries.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#include "Queries.h"

Queries::Queries() {
	// TODO Auto-generated constructor stub

}

Queries::Queries(Tuple tuple, string name){
    this->tuple = tuple;
    this->name = name;
}

Queries::~Queries() {
	// TODO Auto-generated destructor stub
}

string Queries::toString() const{
	string result = "";
	for(int i=0; i<valueList.size(); i++){
		Token *tmp = valueList[i];
		result += tmp->getTokensValue();
		//cout << "The result is currently: " + result + "\n";
	}
	return result;
}

Tuple Queries::getTuple(){
    if (this->valueList.size() != 0) {
        vector<Token> newTuple;
            for(int i=0; i<valueList.size(); i++){
                Token tempToken = *valueList[i];
                if((tempToken.getTokenType() == ID || tempToken.getTokenType() == STRING) && i != 0){
                    newTuple.push_back(tempToken);
                }
            }
        return *(new Tuple(newTuple));
    }
    else{
        return this->tuple;
    }
}

string Queries::getName(){
	Token tokenName = *valueList[0];
	return tokenName.getTokensValue();
}


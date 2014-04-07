/*
 * Rules.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: raull
 */

#include "Rules.h"

Rules::Rules() {
	// TODO Auto-generated constructor stub

}

Rules::~Rules() {
	// TODO Auto-generated destructor stub
}

string Rules::toString() const{
	string result = "";
	for(int i=0; i<valueList.size(); i++){
		Token *tmp = valueList[i];
		result += tmp->getTokensValue();
		//cout << "The result is currently: " + result + "\n";
	}
	return result;
}


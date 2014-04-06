/*
 * DatalogParser.h
 *
 *  Created on: Feb 18, 2014
 *      Author: raull
 */

/*
 * Created by Raul Lopez Villalpando & Brady Tate Anderson  February 24th, 2014
 * */


#ifndef DATALOGPARSER_H_
#define DATALOGPARSER_H_

#include "Token.h"
#include "Lex.h"
#include "Schemes.h"
#include "Rules.h"
#include "Facts.h"
#include "Queries.h"
#include "Relation.h"
#include "Predicates.h"
#include "Tuple.h"
#include <vector>
#include <set>
#include <iostream>
#include <ctype.h>

using namespace std;

class DatalogParser {
public:

//Constructor:
	DatalogParser(vector<Token*> tokens);

	//DatalogParser(Lex input);
//Destructor:
	virtual ~DatalogParser();


//Methods:
	bool parse();
	void advance();
	void storeToken(Token *token);
	Token* getCurrentToken();
	void createRelationalDatabase();
	void evaluateQueries();

	string toString() const;
//Instance variables

	Token* currentToken;
	Token* prevToken;
	int parseState;
    int parseRuleState;
	vector<Relation> relations;


private:

	//Private methods for parsing tokens
	bool datalogProgram();
	bool parseSchemes();
	bool parseFacts();
	bool parseRules();
	bool parseQueries();

	// Non-terminals
	bool nSchemes();
	bool nScheme();
	bool nSchemeList();
	bool nFacts();
	bool nFact();
	bool nFactList();
	bool nRules();
	bool nRule();
	bool nRuleList();
	bool nQueries();
	bool nQuery();
	bool nQueryList();

	bool nId();
	bool nIdList();
	bool nString();
	bool nStringList();
	bool nHeadPredicate();
	bool nPredicate();
	bool nPredicateList();
	bool nParameter();
	bool nParameterList();
	bool nExpression();
	bool nOperator();

	bool nLeftParen();
	bool nRightParen();
	bool nComma();
	bool nColon();
	bool nPeriod();
	bool nAdd();
	bool nMultiply();
	bool nQMark();
	bool nColonDash();

	vector<Token*> tokenList;
	int index;
	vector<Schemes*> schemes;
	vector<Facts*> facts;
	vector<Rules*> rules;
	vector<Queries*> queries;
	set<string> domain;
};

#endif /* DATALOGPARSER_H_ */

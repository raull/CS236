/*
 * DatalogParser.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: raull
 */

#include "DatalogParser.h"
#include "TokenType.h"
#include <istream>
#include <iterator>
#include <sstream>

#define PARSING_SCHEMES 1
#define PARSING_FACTS 2
#define PARSING_RULES 3
#define PARSING_QUERIES 4


DatalogParser::DatalogParser(vector<Token *> tokens) {
	tokenList = tokens;
	index = 0;
	currentToken = tokens[index];
	prevToken = currentToken;
	parseState = 0;
}

DatalogParser::~DatalogParser() {

}

bool DatalogParser::parse(){
	if(parseSchemes() && parseFacts() && parseRules() && parseQueries()){
		//cout<< toString();
		return true;
	}
	else{
		cout<<"Failure!\n\t" + currentToken->toString();
		return false;
	}
}

// Schemes, Facts, Rules and Queries

bool DatalogParser::parseSchemes(){
	if(nSchemes() && nColon() && nScheme() && nSchemeList()){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::parseFacts(){
	if(nFacts() && nColon() && nFactList()){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::parseRules(){
	if(nRules() && nColon() && nRuleList()){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::parseQueries(){

	if(nQueries() && nColon() && nQuery() && nQueryList()){
		return true;
	}
	else{
		return false;
	}
}

// All the Recursive Functions

bool DatalogParser::nSchemeList(){
	if(nScheme() && nSchemeList()){
		return true;
	}
	// This is the Lambda Case
	else if(currentToken->getTokenType() == ID || (!currentToken->getTokensValue().compare("Facts") && prevToken->getTokenType() == RIGHT_PAREN)){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nFactList(){
	if(nFact() && nFactList()){
		return true;
	}
	// This is the Lambda Case
	else if(currentToken->getTokenType() == ID || currentToken->getTokenType() == PERIOD || ((prevToken->getTokenType() == PERIOD || prevToken->getTokenType() == COLON) && !currentToken->getTokensValue().compare("Rules"))){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nRuleList(){
	if(nRule() && nRuleList()){
		return true;
	}
	// This is the Lambda Case
	else if(nHeadPredicate() || currentToken->getTokenType() == PERIOD || ((prevToken->getTokenType() == PERIOD || prevToken->getTokenType() == COLON) && !currentToken->getTokensValue().compare("Queries"))){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nQueryList(){
	if(nQuery() && nQueryList()){
		return true;
	}
	// This is the Lambda Case
	else if(nPredicate() || (prevToken->getTokenType() == RIGHT_PAREN && currentToken->getTokenType() == Q_MARK)){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nIdList(){
	if((nComma() && nId() && nIdList())){
		return true;
	}
	// This is the Lambda Case
	else if(currentToken->getTokenType() == RIGHT_PAREN && prevToken->getTokenType() == ID){
		return true;
	}
	else
		return false;
}

bool DatalogParser::nParameterList(){
	if(nComma() && nParameter() && nParameterList()){
		return true;
	}
	// This is the Lambda Case
	else if((prevToken->getTokenType() == ID || prevToken->getTokenType() == RIGHT_PAREN || prevToken->getTokenType() == STRING) && currentToken->getTokenType() == RIGHT_PAREN)
	{
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nPredicateList(){
	if(nComma() && nPredicate() && nPredicateList()){
		return true;
	}
	// This is the Lambda Case
	else if(currentToken->getTokenType() == PERIOD && prevToken->getTokenType() == RIGHT_PAREN)
	{
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nStringList(){
	if(nComma() && nString() && nStringList()){
		return true;
	}
	// This is the Lambda Case
	else if(currentToken->getTokenType() == RIGHT_PAREN && prevToken->getTokenType() == STRING){
		return true;
	}
	else
		return false;
}

// All the non-terminal Functions
/*
 * Every non terminal function does not advance on the tokenList since it it not identifying a token
 * it is just determining if a branch or non-terminal is being satisfied
 *
 * */

bool DatalogParser::nScheme(){
	// This is when a Scheme starts so create a Schemes object to store the tokens
	Schemes *myScheme = new Schemes();
	schemes.push_back(myScheme);
	if(nId() && nLeftParen() && nId() && nIdList() && nRightParen()){
		return true;
	}
	else{
		schemes.pop_back();
		return false;
	}
}

bool DatalogParser::nFact(){
	Facts *myFact = new Facts();
	facts.push_back(myFact);
	if(nId() && nLeftParen() && nString() && nStringList() && nRightParen() && nPeriod()){
		return true;
	}
	else{
		facts.pop_back();
		return false;
	}
}

bool DatalogParser::nRule(){
	Rules *myRule = new Rules();
	rules.push_back(myRule);
	if(nHeadPredicate() && nColonDash() && nPredicate() && nPredicateList() && nPeriod()){
		return true;
	}
	else{
		rules.pop_back();
		return false;
	}
}

bool DatalogParser::nQuery(){
	Queries *myQuery = new Queries();
	queries.push_back(myQuery);
	if(nPredicate() && nQMark()){
		return true;
	}
	else{
		queries.pop_back();
		return false;
	}
}

bool DatalogParser::nHeadPredicate(){
	if(nId() && nLeftParen() && nId() && nIdList() && nRightParen()){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nPredicate(){
	if(nId() && nLeftParen() && nParameter() && nParameterList() && nRightParen()){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nParameter(){
	if(nString() || nId() || nExpression()){
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nExpression(){
	if(nLeftParen() && nParameter() && nOperator() && nParameter() && nRightParen()){
		return true;
	}
	else{
		return false;
	}
}


bool DatalogParser::nOperator(){
	if(nAdd() || nMultiply()){
		return true;
	}
	else{
		return false;
	}
}


// All the terminal Functions
/*
 *
 * All the terminal functions advances trough the tokenList since it identifies that a Token actually exist
 * and its valid
 *
 * */


bool DatalogParser::nSchemes(){
	if(!currentToken->getTokensValue().compare("Schemes")){
		//This way we know we are starting a Schemes and we need to store the tokens to the schemes array
		parseState = PARSING_SCHEMES;
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nFacts(){
	if(!currentToken->getTokensValue().compare("Facts")){
		parseState = PARSING_FACTS;
		advance();
		return true;
	}
	else{
		return false;
	}
}


bool DatalogParser::nRules(){
	if(!currentToken->getTokensValue().compare("Rules")){
		parseState = PARSING_RULES;
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nQueries(){
	if(!currentToken->getTokensValue().compare("Queries")){
		parseState = PARSING_QUERIES;
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nId(){
	if(currentToken->getTokenType() == ID){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nString(){
	if(currentToken->getTokenType() == STRING){
		storeToken(currentToken);
		// Only store the domain for Facts
		if(parseState == PARSING_FACTS){
			domain.insert(currentToken->getTokensValue());
		}
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nColon(){
	if(!currentToken->getTokensValue().compare(":")){
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nComma(){
	if(!currentToken->getTokensValue().compare(",")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nPeriod(){
	if(!currentToken->getTokensValue().compare(".")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nLeftParen()
{
	if(!currentToken->getTokensValue().compare("(")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nRightParen()
{
	if(!currentToken->getTokensValue().compare(")")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nAdd()
{
	if(!currentToken->getTokensValue().compare("+")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nMultiply()
{
	if(!currentToken->getTokensValue().compare("*")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nQMark()
{
	if(!currentToken->getTokensValue().compare("?")){
		storeToken(currentToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

bool DatalogParser::nColonDash()
{
	if(!currentToken->getTokensValue().compare(":-")){
		// Putting White space before and after a Colon Dash token since that is the format
		Token *whiteSpaceToken = new Token(WHITESPACE," ",0);
		storeToken(whiteSpaceToken);
		storeToken(currentToken);
		storeToken(whiteSpaceToken);
		advance();
		return true;
	}
	else{
		return false;
	}
}

// Helper methods for advancing trough tokens and output them

void DatalogParser::storeToken(Token* token){
	// Set up the flags to know which section is getting parsed and know eher to store the tokens to output
	if(parseState == PARSING_SCHEMES){
		schemes.back()->valueList.push_back(token);
	}
	else if(parseState == PARSING_FACTS){
		facts.back()->valueList.push_back(token);
	}
	else if(parseState == PARSING_RULES){
		rules.back()->valueList.push_back(token);
	}
	else if(parseState == PARSING_QUERIES){
		queries.back()->valueList.push_back(token);
	}
}

void DatalogParser::advance(){
	// - 2 since the EOF is the last on the list and we don't need it
	if(index < tokenList.size() - 2){
		index++;
		prevToken = currentToken;
		currentToken = tokenList[index];
	}
}

Token* DatalogParser::getCurrentToken(){
	return tokenList[index];
}

void DatalogParser::createRelationalDatabase(){
	//Start Creating the Relations

	//Creating Schemes
	for(int i=0; i<schemes.size(); i++){
		Relation newRelation;
		newRelation.schema = schemes[i]->getSchema();
		newRelation.name = schemes[i]->getName();
		relations.push_back(newRelation);
	}
	//Relating facts to the relations
	for(int i=0; i<facts.size(); i++){
		for(int j=0; j<relations.size(); j++){
			if(!facts[i]->getName().compare(relations[j].name)){
				relations[j].addTuple(facts[i]->getTuple());
			}
		}
	}

	//Evaluate
	this->evaluateQueries();
}

void DatalogParser::evaluateQueries(){
	//cout << "\n Parsing Queries:  ("<< queries.size() <<")";
	for(int i=0; i<queries.size(); i++){
		for(int j=0; j<relations.size(); j++){
			if(!queries[i]->getName().compare(relations[j].name)){
				cout << (relations[j].parse(*queries[i]));
			}
		}
	}
}

string DatalogParser::toString() const{
	stringstream result;
	result << "Success!\nSchemes(" << schemes.size() << "):";
	for(int i=0; i<schemes.size(); i++){
		result << "\n  " << schemes[i]->toString();
	}
	result << "\nFacts(" << facts.size() << "):";
	for(int i=0; i<facts.size(); i++){
		result << "\n  " << facts[i]->toString();
	}
	result << "\nRules(" << rules.size() << "):";
	for(int i=0; i<rules.size(); i++){
		result << "\n  " << rules[i]->toString();
	}
	result << "\nQueries(" << queries.size() << "):";
	for(int i=0; i<queries.size(); i++){
		result << "\n  " << queries[i]->toString();
	}
	result << "\nDomain(" << domain.size() << "):";
	set<string>::iterator iter;
	for(iter=domain.begin(); iter!=domain.end();++iter){
		result << "\n  " << (*iter);
	}

	return result.str();
}

#include "Lex.h"

#include "Input.h"
#include "TokenType.h"
#include "Utils.h"
#include "DatalogParser.h"
#include <ctype.h>
#include <iostream>

using namespace std;

Lex::Lex() {
	input = new Input();
    generateTokens(input);
}

Lex::Lex(const char* filename) {
    input = new Input(filename);
    generateTokens(input);
}

Lex::Lex(istream& istream) {
    input = new Input(istream);
    generateTokens(input);
}

Lex::Lex(const Lex& lex) {
    input = new Input(*lex.input);
    tokens = new vector<Token*>();

    vector<Token*>::iterator iter;
    for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
        Token* newToken = new Token(**iter);
        tokens->push_back(newToken);
    }

    index = lex.index;
    state = lex.state;
}

Lex::~Lex(){
    for (int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
    }
    delete tokens;
    delete input;
}

bool Lex::operator==(const Lex& lex) {
    bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
    if(result) {
        vector<Token*>::iterator iter1;
        vector<Token*>::iterator iter2;
        iter1 = tokens->begin();
        iter2 = lex.tokens->begin();
        while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
            result = **iter1 == **iter2;
            iter1++;
            iter2++;
        }
        result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
    }
    return result;
}

string Lex::toString() const {
    int count = 0;
    string result;
    while(count < tokens->size()) {
        Token* token = (*tokens)[count];
        result += token->toString();
        count++;
    }
    result += "Total Tokens = ";
    string countToString;
    result += itoa(countToString, count);
    result += "\n";
    return result;
}

void Lex::generateTokens(Input* input) {
    tokens = new vector<Token*>();
    index = 0;

    state = Start;
    while(state != End) {
        state = nextState();
    }
}

Token* Lex::getCurrentToken() {
    return (*tokens)[index];
}

void Lex::advance() {
    index++;
}

bool Lex::hasNext() {
    return index < tokens->size();
}

State Lex::nextState() {
    State result;
    char character;
    string finalString;
    switch(state) {
        case Start:               result = getNextState(); break;
        case Comma:               emit(COMMA); result = getNextState(); break;
        case Period:              emit(PERIOD); result = getNextState(); break;
        case QuestionMark:		  emit(Q_MARK); result = getNextState(); break;
        case leftParen:			  emit(LEFT_PAREN); result = getNextState(); break;
        case rightParen:		  emit(RIGHT_PAREN); result = getNextState(); break;
        case Multiply:			  emit(MULTIPLY); result = getNextState(); break;
        case Add:				  emit(ADD); result = getNextState(); break;
        case Undefined:			  emit(UNDEFINED); result = getNextState(); break;
        case Whitespace:		  input->mark(); result = getNextState(); break;
        case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
        case ProcessWord:
        	character = input->getCurrentCharacter();
        	if(isalnum(character))
        	{
        		result = ProcessWord;
        		input->advance();
        	}
        	else
        	{
				finalString = input->getTokensValue();

				if(!finalString.compare("Schemes"))
				{
					emit(SCHEMES);
					result = getNextState();
				}
				else if(!finalString.compare("Queries"))
				{
					emit(QUERIES);
					result = getNextState();
				}
				else if(!finalString.compare("Rules"))
				{
					emit(RULES);
					result = getNextState();
				}
				else if(!finalString.compare("Facts"))
				{
					emit(FACTS);
					result = getNextState();
				}
				else
				{
					emit(ID);
					result = getNextState();
				}
        	}
        	break;
        case SawColon:
            character = input->getCurrentCharacter();
            if(character == '-') {
                result = Colon_Dash;
                input->advance();
            } else { //Every other character
            	emit(COLON); result = getNextState(); break;
                //throw "ERROR:: in case SawColon:, Expecting  '-' but found " + character + '.';
            }
            break;
        case SawPound:
        	character = input->getCurrentCharacter();
        	if(character == '|')
        	{
        		result = ProcessBlockComment;
        		input->advance();
        	}
        	else
        	{
        		result = ProcessComment;
        	}
        	break;
        case ProcessComment:
        	character = input->getCurrentCharacter();
        	if(character == -1 || character == '\n')
        	{
        		emit(COMMENT);
        		result = getNextState();
        	}
        	else
        	{
        		result = ProcessComment;
        		input->advance();
        	}
        	break;
        case ProcessBlockComment:
        	character = input->getCurrentCharacter();
        	if(character == '|')
        	{
        		input->advance();
        		if(input->getCurrentCharacter() == '#')
        		{
        			input->advance();
        			emit(COMMENT);
        			result = getNextState();
        		}
        		else
        		{
        			result = ProcessBlockComment;
        		}
        	}
        	else if(character == -1)
        	{
        		emit(UNDEFINED);
        		result = getNextState();
        	}
        	else
        	{
        		result = ProcessBlockComment;
            	input->advance();
        	}
        	break;
        case SawAQuote:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            	//throw "ERROR:: in Saw_A_Quote::nextState, reached EOF before end of string.";
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case ProcessingString:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            	//throw "ERROR:: in ProcessingString::nextState, reached EOF before end of string.";
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case PossibleEndOfString:
            if(input->getCurrentCharacter() == '\'') {
                input->advance();
                result = ProcessingString;
            } else { //Every other character
                emit(STRING);
                result = getNextState();
            }
            break;
        case End:
            throw "ERROR:: in End state:, the Input should be empty once you reach the End state.";
            break;
    };
    return result;
}

State Lex::getNextState() {
    State result;
    char currentCharacter = input->getCurrentCharacter();

    //The handling of checking for whitespace and setting the result to Whitespace and
    //checking for letters and setting the result to Id will probably best be handled by
    //if statements rather then the switch statement.
    if(isspace(currentCharacter))
	{
		result = Whitespace;
	}
    else if(isalpha(currentCharacter))
    {
    	result = ProcessWord;
    }
	else
	{
		switch(currentCharacter) {
			case ','  : result = Comma; break;
			case '.'  : result = Period; break;
			case ':'  : result = SawColon; break;
			case '\'' : result = SawAQuote; break;
			case '?'  : result = QuestionMark; break;
			case '('  : result = leftParen; break;
			case ')'  : result = rightParen; break;
			case '*'  : result = Multiply; break;
			case '+'  : result = Add; break;
			case '#'  : result = SawPound; break;
			case -1   : result = End; emit(ENDOF); break;
			default:
				result = Undefined;
				break;
		}
	}

    input->advance();
    return result;
}

void Lex::emit(TokenType tokenType) {
    Token* token = new Token(tokenType, input->getTokensValue(), input->getCurrentTokensLineNumber());
    storeToken(token);
    input->mark();
}

void Lex::storeToken(Token* token) {
    //This section shoud ignore whitespace and comments and change the token type to the appropriate value
    //if the value of the token is "Schemes", "Facts", "Rules", or "Queries".

	if(token->getTokenType() != COMMENT){
		tokens->push_back(token);
	}
}

vector<Token*> Lex::getTokenList(){
	return *tokens;
}

int main(int argc, char* argv[]) {
    Lex lex(argv[1]);
    //Lex lex("TestFile1.txt");
    DatalogParser datalogProgram(lex.getTokenList());
    datalogProgram.parse();
    datalogProgram.createRelationalDatabase();
    
    Token first(ID, "A", 0);
    Token second(ID, "B", 0);
    Token third(ID, "C", 0);
    
    vector<Token> scheme {first,  second, third};
    
    Token element11(STRING, "a", 0);
    Token element12(STRING, "a", 0);
    Token element13(STRING, "x", 0);
    
    vector<Token> row1 {element11, element12, element13};
    Tuple rowTuple1(row1);
    
    Token element21(STRING, "b", 0);
    Token element22(STRING, "a", 0);
    Token element23(STRING, "c", 0);
    
    vector<Token> row2 {element21, element22, element23};
    Tuple rowTuple2(row2);
    
    Relation relation1(scheme, "relation1");
    relation1.addTuple(row1);
    relation1.addTuple(row2);
    
    Token firstSchema(ID, "B", 0);
    Token secondSchema(ID, "X", 0);
    Token thirdSchema(ID, "C", 0);
    
    vector<Token> secondScheme {firstSchema,  secondSchema, thirdSchema};
    
    Token secondElement11(STRING, "a", 0);
    Token secondElement12(STRING, "a", 0);
    Token secondElement13(STRING, "c", 0);
    
    vector<Token> secondRow1 {element11, element12, element13};
    Tuple secondRowTuple1(row1);
    
    Token secondElement21(STRING, "b", 0);
    Token secondElement22(STRING, "d", 0);
    Token secondElement23(STRING, "d", 0);
    
    vector<Token> secondRow2 {secondElement21, secondElement22, secondElement23};
    Tuple secondRowTuple2(row2);
    
    Relation relation2(secondScheme, "relation2");
    relation2.addTuple(secondRow1);
    relation2.addTuple(secondRow2);
    
    Relation crossProductResult = Relation::crossProduct(relation1,relation2);
    Relation naturalJoinResult = Relation::naturalJoin(relation1, relation2);
    crossProductResult.name = "crossProduct";
    naturalJoinResult.name = "naturalJoin";
    cout << crossProductResult.toString();
    cout << relation1.toString();
    cout << relation2.toString();
    cout << naturalJoinResult.toString();
    
    
    
    
    return 0;
}

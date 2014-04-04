#include "TokenType.h"

using namespace std;

string TokenTypeToString(TokenType tokenType){
    string result = "";
    switch(tokenType){
        case COMMA:              result = "COMMA"; break;
        case PERIOD:             result = "PERIOD"; break;
        case COLON_DASH:         result = "COLON_DASH"; break;
        case Q_MARK:			 result = "Q_MARK"; break;
        case LEFT_PAREN:		 result = "LEFT_PAREN"; break;
        case RIGHT_PAREN:		 result = "RIGHT_PAREN"; break;
        case STRING:             result = "STRING"; break;
        case MULTIPLY:			 result = "MULTIPLY"; break;
        case ADD:				 result = "ADD"; break;
        case COLON:				 result = "COLON"; break;
        case ENDOF:				 result = "EOF"; break;
        case WHITESPACE:		 result = "WHITESPACE"; break;
        case UNDEFINED:			 result = "UNDEFINED"; break;
        case COMMENT:			 result = "COMMENT"; break;
        case SCHEMES:			 result = "SCHEMES"; break;
        case QUERIES:			 result = "QUERIES"; break;
        case FACTS: 			 result = "FACTS"; break;
        case RULES:				 result = "RULES"; break;
        case ID:				 result = "ID"; break;
        case NUL:                result = "NUL"; break;
    }
    return result;
};

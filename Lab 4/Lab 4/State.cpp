#include "State.h"

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
        case SawColon:                   result = "SawColon"; break;
        case Colon_Dash:                 result = "Colon_Dash"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
        case Start:                      result = "Start"; break;
        case QuestionMark:				 result = "QuestionMark"; break;
        case leftParen:					 result = "leftParen"; break;
        case rightParen:				 result = "rightParen"; break;
        case Multiply:					 result = "Multiply"; break;
        case Add:						 result = "Add"; break;
        case Undefined:					 result = "Undefined"; break;
        case Whitespace:				 result = "Whitespace"; break;
        case SawPound:					 result = "SawPound"; break;
        case ProcessComment:			 result = "ProccessComment"; break;
        case ProcessBlockComment:		 result = "ProcessBlockComment"; break;
        case ProcessWord:				 result = "ProcessWord"; break;
        case PosibleEndBlockComment:	 result = "PosibleEndBlockComment"; break;
        case End:                        result = "End"; break;
    }
    return result;
};

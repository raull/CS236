#ifndef STATE_H
#define STATE_H

#include <string>

/**
 * The states of the finite state machine defined in an enumerated type.
 */
enum State {Comma, Period, SawColon, Colon_Dash, SawAQuote, ProcessingString,
            PossibleEndOfString, Start, QuestionMark, leftParen, rightParen, Multiply, Add,
            Whitespace, Undefined, SawPound, ProcessComment, ProcessBlockComment, PosibleEndBlockComment,
            ProcessWord, End
           };

    /**
     * Converts a state to a string.
     * 
     * Parameters: state -- the state to be converted to a string.
     * PreCondition: none
     * Postcondition: result = the string representation of the state which
     *                         looks exactly like its State name.
     */
    std::string StateToString(State state);
#endif

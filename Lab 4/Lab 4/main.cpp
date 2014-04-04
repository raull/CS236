//
//  main.cpp
//  Lab 4
//
//  Created by Raul Lopez Villalpando on 3/31/14.
//  Copyright (c) 2014 Raul Lopez Villalpando. All rights reserved.
//

#include <iostream>
#include "Lex.h"
#include "DatalogParser.h"

int main(int argc, const char * argv[])
{
    Lex lex(argv[1]);
    DatalogParser datalogProgram(lex.getTokenList());
    datalogProgram.parse();
    datalogProgram.createRelationalDatabase();
    //datalogProgram.toString();
    return 0;
}


/*
 * Relation.h
 *
 *  Created on: Mar 15, 2014
 *      Author: raull
 */

#ifndef RELATION_H_
#define RELATION_H_

#include "Tuple.h"
#include "Schemes.h"
#include "Token.h"
#include "Queries.h"
#include <vector>
#include <set>

using namespace std;

class Relation {
public:

	//Instance Variable
	set<Tuple> rows;
	vector<Token> schema;
	string name;
	//Relation editedRelation;

	//Constructor and Destructor
	Relation();
	Relation(set<Tuple> tuples, vector<Token> schema);
	Relation(vector<Token> schema, string name);
	virtual ~Relation();

	//Instance Methods
	string toString();
	string toFinalString(Queries query);
	void addTuple(Tuple tuple);
	void deleteTuple(int index);
	string parse(Queries query);
    Relation parse(Tuple tuple);
    
    //Relation Operations
    static Relation crossProduct(Relation relation1, Relation relation2);
    static Relation naturalJoin(Relation relation1, Relation relation2);
    Relation rename(Tuple tuple, Relation relation);
	Relation select(Tuple tuple, Relation relation);
	Relation project(Tuple tuple, Relation relation);
    Tuple getRowAtIndex(int index);

private:
	
    

};

#endif /* RELATION_H_ */

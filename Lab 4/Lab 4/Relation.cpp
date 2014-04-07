/*
 * Relation.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: raull
 */

#include "Relation.h"
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>

Relation::Relation() {
	// TODO Auto-generated constructor stub

}

Relation::Relation(set<Tuple> tuples, vector<Token> schema){
	this->rows = tuples;
	this->schema = schema;
	//this->editedRelation = new Relation();
}

Relation::Relation(vector<Token> schema, string name){
	this->schema = schema;
	this->name = name;
	//this->editedRelation = new Relation();
}

Relation::~Relation() {
	// TODO Auto-generated destructor stub
}

string Relation::toString(){
	stringstream result;
	result << "Relation:" << name << "\nSchema:\n(";
	for(int i=0; i<schema.size(); i++){
		if(i != schema.size() - 1)
			result << schema[i].getTokensValue() << ", ";
		else
			result << schema[i].getTokensValue() << ")";
	}
	for(int i=0; i<rows.size(); i++){
		result << "\n" << getRowAtIndex(i).toString();
	}
	result << "\n";
	return result.str();
}

string Relation::toFinalString(Queries query){
	stringstream result;
	if(rows.size()>0){
		result << query.toString() << " Yes(" << rows.size() << ")\n";
		for(int i=0; i<rows.size(); i++){
			for(int j=0; j<schema.size(); j++){
				if(j==0){
					result << "  " << schema[j].getTokensValue() << "=" << getRowAtIndex(i).elements[j].getTokensValue();
				}
				else{
					result << ", " << schema[j].getTokensValue() << "=" << getRowAtIndex(i).elements[j].getTokensValue();
				}
			}
			if(schema.size()>0){
				result << "\n";
			}
		}
	}
	else{
		result << query.toString() << " No\n";
	}
	return result.str();
}

void Relation::addTuple(Tuple tuple){
	// Check to see if tuple already exists
//	bool anyMatch = false;
//	for(int i=0; i<rows.size(); i++){
//		bool rowMatch = true;
//		for(int j=0; j<tuple.elements.size(); j++){
//			if(tuple.elements[j].getTokenType() == STRING){
//				if(tuple.elements[j].getTokensValue().compare(getRowAtIndex(i).elements[j].getTokensValue())){
//					// Do nothing
//					rowMatch = false;
//					//cout<< "1";
//				}
//				else{
//					//cout<< "2";
//				}
//			}
//		}
//		if(rowMatch == true){
//			anyMatch = true;
//		}
//	}

//	if(!anyMatch){
		this->rows.insert(tuple);
		//Sort the rows from the relation
//		sort(rows.begin(), rows.end());
//	}
}

string Relation::parse(Queries query){
	Relation editedRelation = *this;

	editedRelation = rename(query.getTuple(), editedRelation);
	editedRelation = select(query.getTuple(), editedRelation);
	editedRelation = project(query.getTuple(), editedRelation);

	return editedRelation.toFinalString(query);
}

Relation Relation::parse(Tuple tuple){
    Relation editedRelation = *this;
    
	editedRelation = rename(tuple, editedRelation);
	editedRelation = select(tuple, editedRelation);
	editedRelation = project(tuple, editedRelation);
    
	return editedRelation;

}

Relation Relation::rename(Tuple tuple, Relation relation){

	for(int i=0; i<tuple.elements.size(); i++){
		if(tuple.elements[i].getTokenType() == ID){
			Token *newToken = new Token(ID, tuple.elements[i].getTokensValue() ,relation.schema[i].getLineNumber());
			relation.schema[i] = *newToken;
		}
	}
	return relation;
}

Relation Relation::select(Tuple tuple, Relation relation){
	set<Tuple> newRows;

	for(int i=0; i<relation.rows.size(); i++){
		bool selected = true;
		map<string, string> idMap;
		for(int j=0; j<tuple.elements.size(); j++){
			if(tuple.elements[j].getTokenType() == STRING){
				if(tuple.elements[j].getTokensValue().compare(relation.getRowAtIndex(i).elements[j].getTokensValue())){
					selected = false;
				}
			}
			else if(tuple.elements[j].getTokenType() == ID){
				if(idMap.find(tuple.elements[j].getTokensValue()) != idMap.end()){
					// Key is found
					if(idMap[tuple.elements[j].getTokensValue()] == relation.getRowAtIndex(i).elements[j].getTokensValue()){
						// Passes
					}
					else{
						// Fails
						selected = false;
					}
				}
				else{
					// Key was not found
					idMap[tuple.elements[j].getTokensValue()] = relation.getRowAtIndex(i).elements[j].getTokensValue();
				}
			}
		}

		if(selected)
		{
			newRows.insert(relation.getRowAtIndex(i));
		}
	}

	relation.rows = newRows;

	return relation;
}


Relation Relation::project(Tuple tuple, Relation relation){

	// Create a new Relation that add only the elements and schema that we are projecting

	set<Tuple> newRows;

	vector<Token> newSchema;
	// check rows
	for(int i=0; i<relation.rows.size(); i++){
		vector<string> projectedIds;
		vector<Token> newElements;
		for(int j=0; j<tuple.elements.size(); j++){
			if(tuple.elements[j].getTokenType() == ID){
				bool isPresent = find(projectedIds.begin(), projectedIds.end(), tuple.elements[j].getTokensValue()) != projectedIds.end();
				//If we haven't projected this ID before
				if(!isPresent){
					projectedIds.push_back(tuple.elements[j].getTokensValue());
					if(i==0){
						newSchema.push_back(relation.schema[j]);
					}
					newElements.push_back(relation.getRowAtIndex(i).elements[j]);
				}
			}
		}
		Tuple newTuple(newElements);
		newRows.insert(newTuple);
	}

	relation.rows = newRows;
	relation.schema = newSchema;

	return relation;
}

Relation Relation::crossProduct(Relation relation1, Relation relation2){
    Relation newRelation;
    for (int i=0; i<relation1.rows.size(); i++) {
        for (int j=0; j<relation2.rows.size(); j++) {
            vector<Token> newVector = relation1.getRowAtIndex(i).elements;
            newVector.insert(newVector.end(), relation2.getRowAtIndex(i).elements.begin() ,relation2.getRowAtIndex(j).elements.end());
            Tuple newTuple(newVector);
            newRelation.addTuple(newTuple);
        }
    }
    
    vector<Token> newSchema = relation1.schema;
    newSchema.insert(newSchema.end(), relation2.schema.begin(), relation2.schema.end());
    
    newRelation.schema = newSchema;
    
    return newRelation;
}

Relation Relation::naturalJoin(Relation relation1, Relation relation2){
    Relation newRelation;
    vector<pair<int, int>> pairIndexes;
    //Determine which columns relations have in common
    for (int i=0; i<relation1.schema.size(); i++) {
        for (int j=0; j<relation2.schema.size(); j++) {
            if(relation1.schema[i].getTokenType() == ID && relation2.schema[j].getTokenType() == ID &&
               !relation1.schema[i].getTokensValue().compare(relation2.schema[j].getTokensValue())){
                pairIndexes.push_back(make_pair(i, j));
            }
        }
    }
    
    for (int i=0; i<relation1.rows.size(); i++) {
        for (int j=0; j<relation2.rows.size(); j++) {
            bool equal = true;
            for (int k=0; k<pairIndexes.size(); k++) {
                if (relation1.getRowAtIndex(i).elements[pairIndexes[k].first].getTokensValue().compare(relation2.getRowAtIndex(j).elements[pairIndexes[k].second].getTokensValue())) {
                    equal = false;
                }
            }
            if (equal) {
                vector<Token> newVector = relation1.getRowAtIndex(i).elements;
                vector<Token> vectorToProject = relation2.getRowAtIndex(j).elements;
                
                //Eliminate Intersected Columns
                for (int k=pairIndexes.size() - 1.0; k>=0; k--) {
                    vectorToProject.erase(vectorToProject.begin() + pairIndexes[k].second);
                }
                
                newVector.insert(newVector.end(), vectorToProject.begin() ,vectorToProject.end());
                Tuple newTuple(newVector);
                newRelation.addTuple(newTuple);
            }
        }
    }
    
    vector<Token> newSchema = relation1.schema;
    vector<Token> schemaToEdit = relation2.schema;
    
    //Eliminate intercept columns in the schema
    for (int i=pairIndexes.size()-1.0; i>=0; i--) {
        schemaToEdit.erase(schemaToEdit.begin() + pairIndexes[i].second);
    }
    newSchema.insert(newSchema.end(), schemaToEdit.begin(), schemaToEdit.end());
    newRelation.schema = newSchema;
    
    return newRelation;
}

Tuple Relation::getRowAtIndex(int index){
    set<Tuple>::iterator it = rows.begin();
    advance(it, index); // now it is advanced by index
    return *it;
}

void Relation::deleteTuple(int index){
    set<Tuple>::iterator it = rows.begin();
    advance(it, index); // now it is advanced by index
	this->rows.erase(it);
}



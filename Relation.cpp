//
// Created by bkweb on 10/15/2021.
//

#include "Relation.h"
#include <sstream>
#include <iostream>

Relation::Relation() {}

Relation::Relation(std::string name, Header header) {
    this->name = name;
    this->header = header;
    this->tuples = std::set<Tuple>();
}

Relation::~Relation() {

}

std::string Relation::toString() {
    std::stringstream s("");
    s << this->name << "(";
    for (unsigned int i = 0; i < header.getAttributes().size(); i++) {
        s << header.getAttributes().at(i);
        if (i + 1 < header.getAttributes().size()){
            s << ", ";
        }
    }
    s << "):\n";
    for (Tuple t : tuples) {
        std::vector<std::string> values = t.getValues();
        for (auto it = values.begin(); it != values.end(); it++){
            s << *it;
            if (std::next(it) != values.end()){
                s << ", ";
            }
        }
        s << "\n";
    }
    return s.str();
}

void Relation::addTuple(Tuple tuple) {
    tuples.insert(tuple);
}

Relation* Relation::select(unsigned int colIndex, std::string value) {
    Relation* newRelation = new Relation(name, header);
    for (Tuple tuple : tuples) {
        if (tuple.getValues().at(colIndex) == value){
            newRelation->addTuple(tuple);
        }
    }
    return newRelation;
}

Relation* Relation::select(unsigned int index1, unsigned int index2) {
    Relation* newRelation = new Relation(name, header);
    for (const Tuple& tuple : tuples) {
        if (tuple.getValues().at(index1) == tuple.getValues().at(index2)) {
            newRelation->addTuple(tuple);
        }
    }
    return newRelation;
}

Relation* Relation::project(std::vector<unsigned int> indices) {
    Header newHeader = Header();
    std::vector<std::string> newValues = std::vector<std::string>();
    for (unsigned int index : indices){
        newHeader.addAttribute(header.getAttributes().at(index));
    }
    auto* newRelation = new Relation(name, newHeader);
    for (Tuple tuple : tuples){
        Tuple newTuple = Tuple();
        for (unsigned int index : indices){
            newTuple.addValue(tuple.getValues().at(index));
        }
        newRelation->addTuple(newTuple);
    }

    return newRelation;
}

Relation* Relation::rename(std::vector<std::string> attributes) {
    std::cout << "FIX RENAME";
    return new Relation();
}


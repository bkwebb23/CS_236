//
// Created by bkweb on 10/15/2021.
//

#include "Relation.h"
#include <sstream>

Relation::Relation() = default;

Relation::Relation(std::string name, const Header& header) {
    this->name = name;
    this->header = header;
    this->tuples = std::set<Tuple>();
}

Relation::~Relation() = default;


std::string Relation::toString() {
    std::stringstream s("");
    for (auto tuple : tuples) {
        s << tuple.toString() << "\n";
    }
    return s.str();
}

void Relation::addTuple(const Tuple& tuple) {
    tuples.insert(tuple);
}

// Returns a relation whose tuples all contain value in column colIndex
Relation Relation::select(unsigned int colIndex, const std::string& value) {
    Relation relation = Relation(name, header);
    for (const Tuple& tuple : tuples) {
        if (tuple.getValues().at(colIndex) == value){
            relation.addTuple(tuple);
        }
    }
    return relation;
}

// Returns a relation where the values at index1 and index2 match for every tuple
Relation Relation::select(unsigned int index1, unsigned int index2) {
    Relation relation = Relation(name, header);
    for (const Tuple& tuple : tuples) {
        if (tuple.getValues().at(index1) == tuple.getValues().at(index2)) {
            relation.addTuple(tuple);
        }
    }
    return relation;
}

//
Relation Relation::project(const std::vector<unsigned int>& indices) {
    Header newHeader = Header();

    // Adds the header attributes corresponding to the passed indices to the new header
    for (unsigned int index : indices){
        newHeader.addAttribute(header.getAttributes().at(index));
    }

    // For each tuple in original relation, adds a new tuple to a new relation only with values corresponding
    //      to the new header
    Relation relation = Relation(name, newHeader);
    for (const Tuple& tuple : tuples){
        Tuple newTuple = Tuple();
        for (unsigned int index : indices){
            newTuple.addValue(tuple.getValues().at(index));
        }
        relation.addTuple(newTuple);
    }
    return relation;
}

// As the dimension of the header's attributes is equivalent to the vector passed to this function,
//      we rename each attribute in the header with the string in the corresponding position of the passed vector
void Relation::rename(std::vector<std::string> attributes) {
    for (unsigned int i = 0; i < attributes.size(); i++) {
        header.renameAttribute(i, attributes.at(i));
    }
}

std::set<Tuple> Relation::getTuples() {
    return tuples;
}

const Header &Relation::getHeader() const {
    return header;
}




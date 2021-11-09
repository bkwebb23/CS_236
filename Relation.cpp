//
// Created by bkweb on 10/15/2021.
//

#include "Relation.h"
#include <sstream>
#include "iostream"


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

Header Relation::combineHeaders(const Relation& rhRelation) {
    Header prodHeader = header;
    std::vector<std::string> tempAttributes = rhRelation.getHeader().getAttributes();
    std::vector<std::string> attributesToAdd;

    bool match = false;
    for (unsigned int i = 0; i < rhRelation.getHeader().getAttributes().size(); i++){
        match = false;
        for (unsigned int j = 0; j < getHeader().getAttributes().size(); j++){
            if (rhRelation.getHeader().getAttributes().at(i) == getHeader().getAttributes().at(j)) {
                match = true;
            }
        }
        if (!match) {
            attributesToAdd.push_back(rhRelation.getHeader().getAttributes().at(i));
        }
    }

    for (const std::string& attribute : attributesToAdd) {
        prodHeader.addAttribute(attribute);
    }
    return prodHeader;
}

bool Relation::isJoinable(const Tuple& tuple1, const Tuple& tuple2,
                          const std::map<unsigned int, unsigned int>& matchingIndices) {
    bool status = true;
    for (const auto& kv : matchingIndices) {
        if (tuple1.getValues().at(kv.first) != tuple2.getValues().at(kv.second)) {
            status = false;
        }
    }
    return status;
}

Tuple Relation::combineTuples(const Tuple& tuple1, const Tuple& tuple2,
                             const std::map<unsigned int, unsigned int>& matchingIndices) {
    Tuple combined = tuple1;

    bool isNew = true;
    for (unsigned int j = 0; j < tuple2.getValues().size(); j++) {
        isNew = true;
        for (const auto& kv : matchingIndices) {
            if (j == kv.second) {
                isNew = false;
            }
        }
        if (isNew) {
            combined.addValue(tuple2.getValues().at(j));
        }
    }

    return combined;
}

std::string Relation::relUnion(const Relation& relation) {
    std::stringstream s("");
    for (const auto& tuple : relation.getTuples()) {
        if(tuples.insert(tuple).second) {
            s << "  ";
            for (unsigned int j = 0; j < tuple.getValues().size(); j++) {
                s << header.getAttributes().at(j) << "=" << tuple.getValues().at(j);
                if (j + 1 < tuple.getValues().size()){
                    s << ", ";
                }
            }
            s << "\n";
        }
    }
    return s.str();
}

Relation Relation::naturalJoin(const Relation& rhRelation) {
    Header joinedHeader = combineHeaders(rhRelation);
    Relation joinedRel = Relation("temp", joinedHeader);

    std::map<unsigned int, unsigned int> matchingIndices;
    std::vector<unsigned int> rhColsNew;

    for (unsigned int i = 0; i < header.getAttributes().size(); i++) {
        for (unsigned int j = 0; j < rhRelation.getHeader().getAttributes().size(); j++) {
            if (header.getAttributes().at(i) == rhRelation.getHeader().getAttributes().at(j)) {
                matchingIndices[i] = j;
                rhColsNew.push_back(j);
                break;
            }
        }
    }

    /* This code below may or may not work, but it was the combine header stuff above that was giving me errors*/
    for (const auto& lhTuple : tuples) {
        for (const auto& rhTuple : rhRelation.getTuples()) {

            if (isJoinable(lhTuple,rhTuple,matchingIndices)) {
                joinedRel.addTuple(combineTuples(lhTuple,rhTuple,matchingIndices));
            }
        }
    }
    return joinedRel;
}

std::set<Tuple> Relation::getTuples() const {
    return tuples;
}

Header Relation::getHeader() const {
    return header;
}

void Relation::setName(const std::string &newName) {
    Relation::name = newName;
}

const std::string &Relation::getName() const {
    return name;
}





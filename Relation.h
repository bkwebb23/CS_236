//
// Created by bkweb on 10/15/2021.
//

#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>
#include "Tuple.h"
#include "Header.h"

class Relation {
private:
    std::string name;
    std::set<Tuple> tuples;
    Header header;

public:
    Relation();
    Relation(std::string name, Header header);
    ~Relation();

    Relation* select(unsigned int colIndex, std::string value);
    Relation* select(unsigned int index1, unsigned int index2);
    Relation* project(std::vector<unsigned int> indices);
    Relation* rename(std::vector<std::string> attributes);

    std::string toString();
    void addTuple(Tuple tuple);
    void setName(std::string n);
    std::set<Tuple> getTuples();
};


#endif //RELATION_H

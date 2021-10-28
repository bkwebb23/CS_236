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
    Relation(std::string name, const Header& header);
    ~Relation();

    Relation select(unsigned int colIndex, const std::string& value);
    Relation select(unsigned int index1, unsigned int index2);
    Relation project(const std::vector<unsigned int>& indices);
    void rename(std::vector<std::string> attributes);

    std::string toString();
    void addTuple(const Tuple& tuple);
    std::set<Tuple> getTuples();

    const Header &getHeader() const;
};


#endif //RELATION_H

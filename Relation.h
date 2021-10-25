//
// Created by bkweb on 10/15/2021.
//

#ifndef RELATION_H
#define RELATION_H

#include <set>
#include "Tuple.h"
#include <string>
#include "Header.h"

class Relation {
private:
    std::string name;
    std::set<Tuple> tuples;
    Header header;

public:
    Relation();
    ~Relation();

    std::string toString();
};


#endif //RELATION_H

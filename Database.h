//
// Created by bkweb on 10/15/2021.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include "Relation.h"
#include "Header.h"
#include <string>
#include "Tuple.h"

class Database {
private:
    std::map<std::string, Relation> map;
public:
    Database();
    ~Database();

    std::map<std::string, Relation> &getMap();
    void addRelation(std::string name, Header header);
    void populateRelation(std::string name, Tuple tuple);

    std::string toString();
};


#endif //DATABASE_H

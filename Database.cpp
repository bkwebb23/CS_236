//
// Created by bkweb on 10/15/2021.
//

#include <map>
#include <sstream>
#include "Database.h"

Database::Database() {
    this->map=std::map<std::string, Relation>();
}

Database::~Database() {

}

std::map<std::string, Relation> &Database::getMap() {
    return map;
}

void Database::addRelation(std::string name, Header header) {
    map[name] = Relation(name, header);
}

std::string Database::toString() {
    std::stringstream s("");
    for (auto& kv : map){
        s << kv.second.toString();
    }
    return s.str();
}

void Database::populateRelation(std::string name, Tuple tuple) {
    map[name].addTuple(tuple);
}


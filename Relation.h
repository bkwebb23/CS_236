//
// Created by bkweb on 10/15/2021.
//

#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>
#include <map>
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
    Relation naturalJoin(const Relation& relation);
    std::string relUnion(const Relation& relation);
    void rename(std::vector<std::string> attributes);

    void addTuple(const Tuple& tuple);
    void setName(const std::string &newName);

    const std::string &getName() const;

    std::string toString();
    std::set<Tuple> getTuples() const;
    Header getHeader() const;
    Header combineHeaders(const Relation& relation);
    static bool isJoinable(const Tuple& tuple1, const Tuple& tuple2, const std::map<unsigned int, unsigned int>& matchingIndices);
    static Tuple combineTuples(const Tuple& tuple1, const Tuple& tuple2, const std::map<unsigned int, unsigned int>& matchingIndices);
};


#endif //RELATION_H

//
// Created by bkweb on 9/29/2021.
//

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <string>
#include <set>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
public:
    DatalogProgram();
    ~DatalogProgram();
    std::string toString();

    void addScheme(Predicate *givenPredicate);
    void addFact(Predicate* givenPredicate);
    void addQuery(Predicate* givenPredicate);
    void addRule(Rule* givenRule);

private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domain;
};


#endif //DATALOGPROGRAM_H

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <string>
#include <set>
#include "Predicate.h"
#include "Rule.h"


class DatalogProgram {
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domain;
public:
    DatalogProgram();
    ~DatalogProgram();
    std::string toString();

    void addScheme(Predicate *givenPredicate);
    void addFact(Predicate* givenPredicate);
    void addQuery(Predicate* givenPredicate);
    void addRule(Rule* givenRule);
    void computeDomain();

    const std::vector<Predicate *> &getSchemes() const;
    const std::vector<Predicate *> &getFacts() const;
};


#endif //DATALOGPROGRAM_H

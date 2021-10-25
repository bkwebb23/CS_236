//
// Created by bkweb on 9/30/2021.
//

#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>
#include "Predicate.h"
#include "Parameter.h"

class Rule {
private:
    Predicate *headPredicate;
    std::vector<Predicate*> bodyPredicates;
public:
    Rule();
    ~Rule();


    Predicate *getHeadPredicate() const;
    void setHeadPredicate(Predicate *headPredicate);
    const std::vector<Predicate *> &getBodyPredicates() const;
    void setBodyPredicates(const std::vector<Predicate *> &bodyPredicates);
    void addBodyPredicate(Predicate *bodyPredicate);

    std::string toString();
};


#endif //RULE_H

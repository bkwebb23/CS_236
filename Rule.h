//
// Created by bkweb on 9/30/2021.
//

#ifndef RULE_H
#define RULE_H

#include <string>
#include "Predicate.h"
#include "Parameter.h"

class Rule {
private:
    Predicate
public:
    Rule();
    ~Rule();
    std::string toString();
};


#endif //RULE_H

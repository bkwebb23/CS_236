//
// Created by bkweb on 9/30/2021.
//

#include "Rule.h"
#include <sstream>

Rule::Rule() {
    this->headPredicate = new Predicate();
    this->bodyPredicates = std::vector<Predicate*>();
}

Rule::~Rule() {

}

std::string Rule::toString() {
    std::stringstream s;
    s << headPredicate->toString() << " :- ";
    for (unsigned int i = 0; i < bodyPredicates.size(); i++){
        s << bodyPredicates.at(i)->toString();
    }
    return s.str();
}

Predicate *Rule::getHeadPredicate() const {
    return headPredicate;
}

void Rule::setHeadPredicate(Predicate *predicate) {
    Rule::headPredicate = predicate;
}

const std::vector<Predicate *> &Rule::getBodyPredicates() const {
    return bodyPredicates;
}

void Rule::setBodyPredicates(const std::vector<Predicate *> &predicates) {
    Rule::bodyPredicates = predicates;
}

void Rule::addBodyPredicate(Predicate *bodyPredicate) {
    bodyPredicates.push_back(bodyPredicate);
}



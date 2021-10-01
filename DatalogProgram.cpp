//
// Created by bkweb on 9/29/2021.
//

#include "DatalogProgram.h"
#include <sstream>

DatalogProgram::DatalogProgram() {
}

DatalogProgram::~DatalogProgram() {
}

void DatalogProgram::addScheme(Predicate *givenPredicate) {
    //Predicate* predicate = &givenPredicate;
    schemes.push_back(givenPredicate);
}

void DatalogProgram::addFact(Predicate *givenPredicate) {
    facts.push_back(givenPredicate);
}

void DatalogProgram::addRule(Rule *givenRule) {
    rules.push_back(givenRule);
}

void DatalogProgram::addQuery(Predicate *givenPredicate) {
    queries.push_back(givenPredicate);
}

void DatalogProgram::computeDomain() {
    std::vector<Parameter*> factParameters = std::vector<Parameter*>();
    for (unsigned int i = 0; i < facts.size(); i++) {
        factParameters = facts.at(i)->getParameters();
        for (unsigned int j = 0; j < factParameters.size(); j++){
            domain.insert(factParameters.at(j)->getName());
        }
    }
}

std::string DatalogProgram::toString() {
    std::stringstream s;
    s << "Schemes(" << std::to_string(schemes.size()) << "):\n";
    for (unsigned int i = 0; i < schemes.size(); i++) {
        s << "  " << schemes.at(i)->toString() << "\n";
    }
    s << "Facts(" << std::to_string(facts.size()) << "):\n";
    for (unsigned int i = 0; i < facts.size(); i++) {
        s << "  " << facts.at(i)->toString() << ".\n";
    }
    s << "Rules(" << std::to_string(rules.size()) << "):\n";
    for (unsigned int i = 0; i < rules.size(); i++) {
        s << "  " << rules.at(i)->toString() << ".\n";
    }
    s << "Queries(" << std::to_string(queries.size()) << "):\n";
    for (unsigned int i = 0; i < queries.size(); i++) {
        s << "  " << queries.at(i)->toString() << "?\n";
    }
    computeDomain();
    s << "Domain(" << std::to_string(domain.size()) << "):\n";
    std::set<std::string>::iterator it;
    for (const auto& f : domain) {
        s << "  " << f << "\n";
    }
    return s.str();
}


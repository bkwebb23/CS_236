//
// Created by bkweb on 9/30/2021.
//

#include "Predicate.h"
#include <sstream>


Predicate::Predicate() {
    this->name = std::string();
    this->parameters = std::vector<Parameter*>();
}

Predicate::Predicate(std::string id) {
    this->name = id;
    this->parameters = std::vector<Parameter*>();
}

Predicate::~Predicate() {
//    for (unsigned int i = 0; i < parameters.size(); i++){
//        delete parameters.at(0);
//    }
}

std::string Predicate::toString() {
    std::stringstream s;
    s << name << "(";
    for (unsigned int i =0; i < parameters.size(); i++) {
        if (i != 0) {
            s << ",";
        }
        s << parameters.at(i)->toString();
    }
    s << ")";
    return s.str();
}

const std::string &Predicate::getName() const {
    return name;
}

void Predicate::setName(const std::string &id) {
    Predicate::name = id;
}

const std::vector<Parameter *> &Predicate::getParameters() const {
    return parameters;
}

void Predicate::addParameter(Parameter* givenParameter) {
    Predicate::parameters.push_back(givenParameter);
}


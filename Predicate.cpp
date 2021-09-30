//
// Created by bkweb on 9/30/2021.
//

#include "Predicate.h"

Predicate::Predicate() {}

Predicate::~Predicate() {

}

std::string Predicate::toString() {
    return std::string();
}

const std::string &Predicate::getName() const {
    return name;
}

void Predicate::setName(const std::string &name) {
    Predicate::name = name;
}

const std::vector<Parameter *> &Predicate::getParameters() const {
    return parameters;
}

void Predicate::setParameters(const std::vector<Parameter *> &parameters) {
    Predicate::parameters = parameters;
}

void Predicate::addParameter(Parameter* parameter) {
    Predicate::parameters.push_back(parameter);
}

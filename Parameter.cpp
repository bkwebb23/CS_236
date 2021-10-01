//
// Created by bkweb on 9/30/2021.
//

#include "Parameter.h"
#include <sstream>

Parameter::Parameter() {
    this->name = "";
    this->type = TokenType::STRING;
}
Parameter::Parameter(std::string id, TokenType givenType) {
    this->name = id;
    this->type = givenType;
}
Parameter::~Parameter() {}

const std::string &Parameter::getName() const {
    return name;
}

void Parameter::setName(const std::string &id) {
    Parameter::name = id;
}

TokenType Parameter::getType() const {
    return type;
}

void Parameter::setType(TokenType givenType) {
    Parameter::type = givenType;
}

std::string Parameter::toString() {
    return name;
}



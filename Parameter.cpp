#include "Parameter.h"

Parameter::Parameter() {
    this->name = "";
    this->type = TokenType::STRING;
}
Parameter::Parameter(std::string id, TokenType givenType) {
    this->name = id;
    this->type = givenType;
}
Parameter::~Parameter() = default;

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



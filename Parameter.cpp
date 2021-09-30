//
// Created by bkweb on 9/30/2021.
//

#include "Parameter.h"

Parameter::Parameter() {}

Parameter::~Parameter() {}

const std::string &Parameter::getName() const {
    return name;
}

void Parameter::setName(std::string &id) {
    Parameter::name = id;
}

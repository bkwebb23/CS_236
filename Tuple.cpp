//
// Created by bkweb on 10/15/2021.
//

#include "Tuple.h"
#include <sstream>

Tuple::Tuple() {

}

Tuple::~Tuple() {

}

const std::vector<std::string> Tuple::getValues() const {
    return values;
}

std::string Tuple::toString() {
    std::stringstream s("");
    s << "'";
    for (unsigned int i = 0; i < values.size(); i++) {
       s << values.at(i);
       if (!values.at(i).empty()) {
           s << "', '";
       } else {
           s << "'";
       }
    }
    return s.str();
}

void Tuple::addValue(std::string value) {
    values.push_back(value);
}

bool Tuple::operator<(const Tuple &rhs) const {
    return values < rhs.values;
}

bool Tuple::operator>(const Tuple &rhs) const {
    return rhs < *this;
}

bool Tuple::operator<=(const Tuple &rhs) const {
    return !(rhs < *this);
}

bool Tuple::operator>=(const Tuple &rhs) const {
    return !(*this < rhs);
}


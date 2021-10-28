//
// Created by bkweb on 10/15/2021.
//

#include "Header.h"

Header::Header() {}
Header::Header(std::vector<std::string> &attributes) : attributes(attributes) {}

Header::~Header() {

}

const std::vector<std::string> &Header::getAttributes() const {
    return attributes;
}

void Header::addAttribute(std::string attribute) {
    attributes.push_back(attribute);
}

void Header::renameAttribute(unsigned int index, std::string name) {
    attributes.at(index) = name;
}


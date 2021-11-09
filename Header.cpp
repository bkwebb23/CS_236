//
// Created by bkweb on 10/15/2021.
//

#include "Header.h"

Header::Header() = default;
Header::~Header() = default;

const std::vector<std::string> &Header::getAttributes() const {
    return attributes;
}

void Header::addAttribute(const std::string& attribute) {
    attributes.push_back(attribute);
}

void Header::renameAttribute(unsigned int index, std::string name) {
    attributes.at(index) = name;
}

unsigned int Header::attributeIndex(std::string attribute) const {
    for (unsigned int i = 0; i < attributes.size(); i++) {
        if (attributes.at(i) == attribute) return i;
    }
    return 0;
}


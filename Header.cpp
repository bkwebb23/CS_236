//
// Created by bkweb on 10/15/2021.
//

#include "Header.h"

Header::Header() {}
Header::Header(const std::vector<std::string> &attributes) : attributes(attributes) {}

Header::~Header() {

}

const std::vector<std::string> &Header::getAttributes() const {
    return attributes;
}


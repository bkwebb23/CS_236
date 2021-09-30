//
// Created by bkweb on 9/29/2021.
//

#include "DatalogProgram.h"
#include <sstream>

DatalogProgram::DatalogProgram() {

}

DatalogProgram::~DatalogProgram() {

}

std::string DatalogProgram::toString() {
    std::stringstream s;
    s << "Schemes(" << std::to_string(schemes.size()) << "):\n";
    for (unsigned int i = 0; i < schemes.size(); i++) {
        s << "  " << schemes.at(i)->toString() << "\n";
    }
    s << "Facts(" << std::to_string(facts.size()) << "):\n";
    for (unsigned int i = 0; i < facts.size(); i++) {
        s << "  " << facts.at(i)->toString() << "\n";
    }
    s << "Rules(" << std::to_string(rules.size()) << "):\n";
    for (unsigned int i = 0; i < rules.size(); i++) {
        s << "  " << rules.at(i)->toString() << "\n";
    }
    s << "Queries(" << std::to_string(queries.size()) << "):\n";
    for (unsigned int i = 0; i < queries.size(); i++) {
        s << "  " << queries.at(i)->toString() << "\n";
    }
    s << "Domain: Fix this!";
    return s.str();
}



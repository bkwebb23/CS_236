//
// Created by bkweb on 10/15/2021.
//

#include "Relation.h"
#include <sstream>

Relation::Relation() {}

Relation::~Relation() {

}

std::string Relation::toString() {
    std::stringstream s("");
    for (Tuple t : tuples) {
        std::vector<std::string> values = t.getValues();
        int attrIndex = 0;
        for (std::string attribute : header.getAttributes()) {
            s << attribute << "='" << values.at(attrIndex) << "'";
            if (!values.at(attrIndex).empty()) {
                s << ", ";
            }
        }
    }
    return s.str();
}

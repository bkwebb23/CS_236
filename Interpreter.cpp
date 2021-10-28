//
// Created by bkweb on 10/27/2021.
//

#include "Interpreter.h"
#include <vector>
#include <string>

Interpreter::Interpreter() {}

Interpreter::Interpreter(const DatalogProgram& myDLProgram) {
    this->dlProgram = myDLProgram;
    for (Predicate* scheme : dlProgram.getSchemes()){
        Header predHead = Header();
        for (Parameter* param : scheme->getParameters()) {
            predHead.addAttribute(param->getName());
        }
        database.addRelation(scheme->getName(), predHead);
    }
    for (Predicate* fact : dlProgram.getFacts()){
        Tuple values = Tuple();
        for (Parameter* param : fact->getParameters()) {
            values.addValue(param->toString());
        }
        database.populateRelation(fact->getName(),values);
    }
}

Interpreter::~Interpreter() {

}

std::string Interpreter::toString() {
    return database.toString();
}



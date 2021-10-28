//
// Created by bkweb on 10/27/2021.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <string>
#include "Parameter.h"
#include <sstream>

class Interpreter {
private:
    DatalogProgram dlProgram;
    Database database;
    std::stringstream s;
public:
    Interpreter();
    Interpreter(const DatalogProgram& myDLProgram);
    ~Interpreter();

    void evaluateAll(const std::vector<Predicate*>& predicates);
    Relation evaluatePredicate(Predicate* p);

    std::string toString();
};

#endif //INTERPRETER_H

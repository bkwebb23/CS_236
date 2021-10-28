//
// Created by bkweb on 10/27/2021.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include <string>
#include "Parameter.h"

class Interpreter {
private:
    DatalogProgram dlProgram;
    Database database;
public:
    Interpreter();
    Interpreter(const DatalogProgram& myDLProgram);
    ~Interpreter();

    std::string toString();
};


#endif //INTERPRETER_H

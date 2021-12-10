//
// Created by bkweb on 10/27/2021.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"
#include "Parameter.h"
#include "Graph.h"
#include <string>
#include <sstream>

class Interpreter {
private:
    DatalogProgram dlProgram;
    Database database;
    std::stringstream s;
    Graph myGraph;

public:
    Interpreter();
    explicit Interpreter(const DatalogProgram& myDLProgram);
    ~Interpreter();

    void evaluateQueries(const std::vector<Predicate*>& predicates);
    void evaluateRules(const std::vector<Rule*>& rules);
    void evaluateRule(Rule* rule);
    Relation evaluatePredicate(Predicate* p, bool isQuery= false);

    std::string toString();
};

#endif //INTERPRETER_H

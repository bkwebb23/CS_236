//
// Created by bkweb on 10/27/2021.
//

#include "Interpreter.h"
#include <algorithm>

Interpreter::Interpreter() {
    this->s = std::stringstream("");
}

Interpreter::Interpreter(const DatalogProgram& myDLProgram) {
    this->dlProgram = myDLProgram;
    this->s = std::stringstream("");
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
    evaluateAll(dlProgram.getQueries());
}

Interpreter::~Interpreter() = default;

Relation Interpreter::evaluatePredicate(Predicate* p) {
    std::string name = p->getName();
    std::string currentVar;
    std::vector<std::string> variables;
    std::vector<unsigned int> variableIndices;
    Relation relation = database.getMap()[name];

    std::vector<std::string> paramNames;
    for (auto param : p->getParameters()) {
        paramNames.push_back(param->getName());
    }

    for (unsigned int i = 0; i < p->getParameters().size(); i++) {
        if (p->getParameters().at(i)->getType() == TokenType::STRING){
           relation = relation.select(i,p->getParameters().at(i)->getName());
        } else if (p->getParameters().at(i)->getType() == TokenType::ID) {
            currentVar = p->getParameters().at(i)->getName();
            if (std::find(variables.begin(),variables.end(),currentVar) == variables.end()){
                variables.push_back(currentVar);
                variableIndices.push_back(i);
            } else {
                auto it = std::find(paramNames.begin(),paramNames.end(),currentVar);
                int k = it - paramNames.begin();
                relation = relation.select(k,i);
            }
        } else {
            s << "This should never run";
        }
    }

    if (!variableIndices.empty()) {
        relation = relation.project(variableIndices);
        relation.rename(variables);
    }
    s << p->toString() << "? ";
    if (!relation.getTuples().empty()) {
        s << "Yes(" << std::to_string(relation.getTuples().size()) << ")\n";
        if (!variableIndices.empty()) {
            for (const auto& tuple : relation.getTuples()) {
                s << "  ";
                for (unsigned int j = 0; j < relation.getHeader().getAttributes().size(); j++) {
                    s << relation.getHeader().getAttributes().at(j) << "=" << tuple.getValues().at(j);
                    if (j + 1 < relation.getHeader().getAttributes().size()) {
                        s << ", ";
                    }
                }
                s << "\n";
            }
            relation.toString();
        }
    } else {
        s << "No\n";
    }


    return relation;
}

std::string Interpreter::toString() {
    return s.str();
}

void Interpreter::evaluateAll(const std::vector<Predicate *>& predicates) {
    for (Predicate* predicate : predicates) {
        evaluatePredicate(predicate);
    }
}





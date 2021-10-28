//
// Created by bkweb on 10/27/2021.
//

#include "Interpreter.h"
#include <vector>
#include <string>
#include "Token.h"

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

Interpreter::~Interpreter() {

}

Relation Interpreter::evaluatePredicate(Predicate* p) {
    std::string name = p->getName();
    Relation relation = database.getMap()[name];
    for (unsigned int i = 0; i < p->getParameters().size(); i++) {
        if (p->getParameters().at(i)->getType() == TokenType::STRING){
            relation.select(i,p->getParameters().at(i)->getName());
        }
    }
    for (unsigned int i = 0; i < p->getParameters().size(); i++) {
        if (p->getParameters().at(i)->getType() == TokenType::ID){
            std::string variable = p->getParameters().at(i)->getName();
            for (unsigned int j = i + 1; j < p->getParameters().size(); j++){
                if (p->getParameters().at(j)->getName() == variable){
                    relation.select(i,j);
                    break;
                }
            }
        }
    }

    std::vector<unsigned int> projectIndices = std::vector<unsigned int>();
    for (unsigned int i = 0; i < p->getParameters().size(); i++){
        if (p->getParameters().at(i)->getType() == TokenType::ID) {
            projectIndices.push_back(i);
        }
    }
    if (!projectIndices.empty()) {
        relation.project(projectIndices);
    }

    s << relation.toString();
    if (!relation.getTuples().empty()) {
        s << "Yes(" << std::to_string(relation.getTuples().size()) << ")\n";
        for (Tuple tuple : relation.getTuples()) {
            s << tuple.toString() << "\n";
        }
    }

    return relation;
}

std::string Interpreter::toString() {
    return s.str();
}

void Interpreter::evaluateAll(std::vector<Predicate *> predicates) {
    for (Predicate* predicate : predicates) {
        evaluatePredicate(predicate);
    }
}





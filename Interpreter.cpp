//
// Created by bkweb on 10/27/2021.
//

#include "Interpreter.h"
#include <algorithm>
#include <iostream>

Interpreter::Interpreter() {
    this->s = std::stringstream("");
}

Interpreter::Interpreter(const DatalogProgram& myDLProgram) {
//    Initialize data members, including the running stringstream
    this->dlProgram = myDLProgram;
    this->s = std::stringstream("");

//    Loops through schemes and creates a new corresponding relation for each
    for (Predicate* scheme : dlProgram.getSchemes()){
        Header predHead = Header();
        for (Parameter* param : scheme->getParameters()) {
            predHead.addAttribute(param->getName());
        }
        database.addRelation(scheme->getName(), predHead);
    }

//    Loops through facts to populate existing relations in the database
    for (Predicate* fact : dlProgram.getFacts()){
        Tuple values = Tuple();
        for (Parameter* param : fact->getParameters()) {
            values.addValue(param->toString());
        }
        database.populateRelation(fact->getName(),values);
    }

//    Loops through all rules, evaluating each
    evaluateRules(dlProgram.getRules());
//    Loops through all queries, evaluating each
    evaluateQueries(dlProgram.getQueries());
}

Interpreter::~Interpreter() = default;

Relation Interpreter::evaluatePredicate(Predicate* p, bool isQuery) {
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
    if (isQuery){
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
    }

    return relation;
}

std::string Interpreter::toString() {
    return s.str();
}

void Interpreter::evaluateQueries(const std::vector<Predicate *>& predicates) {
    s << "Query Evaluation\n";
    for (Predicate* predicate : predicates) {
        evaluatePredicate(predicate, true);
    }
}

void Interpreter::evaluateRules(const std::vector<Rule *> &rules) {

    // OUTPUT DEPENDENCY GRAPHS
    myGraph = Graph(rules);
    std::cout << myGraph.toString();
    std::vector<std::set<int>> forest = myGraph.getSCCS();

    // EVALUATE RULES CORRESPONDING TO EACH SCC
    s << "Rule Evaluation\n";

    // Loop through every SCC
    for (auto& tree : forest) {
        s << "SCC: ";

        // Output the rules in each SCC
        for (auto it = tree.begin(); it != tree.end(); it++) {
            s << "R" << std::to_string(*it);
            if (std::next(it) != tree.end()) {
                s << ",";
            }
        }
        s << "\n";
        bool changed = true;                // Whether or not a loop through the SCC actually produces more facts
        unsigned int prev = 0;              // Number of tuples after previous pass-through
        unsigned int numTuples = 0;         // Current number of tuples in the set of relations
        unsigned int numPasses = 0;         // Total number of times we've looped through this SCC

        // Loop until evaluating each rule in the SCC doesn't produce more tuples
        while(changed) {

            // Evaluate each rule in the SCC
            for (auto& item : tree) {
                evaluateRule(rules.at(item));
                if (tree.size() == 1) {
                    bool recursive = false;
                    std::string rule_name = rules.at(item)->getHeadPredicate()->getName();
                    for (auto& bodyPred : rules.at(item)->getBodyPredicates()) {
                        if (bodyPred ->getName() == rule_name) {
                            recursive = true;
                            break;
                        }
                    }
                    // If the SCC only has one rule, and it doesn't depend on itself, we don't need to loop again
                    if (!recursive) {
                        changed = false;
                    }
                }
            }
            for (const auto& kv : database.getMap()) {
                numTuples += kv.second.getTuples().size();
            }
            if (prev == numTuples) {
                changed = false;
            }
            prev = numTuples;
            numTuples = 0;
            numPasses++;
        }
        s << std::to_string(numPasses) << " passes: ";
        for (auto it = tree.begin(); it != tree.end(); it++) {
            s << "R" << std::to_string(*it);
            if (std::next(it) != tree.end()) {
                s << ",";
            }
        }
        s << "\n";
    }
    s << "\n";
}

void Interpreter::evaluateRule(Rule *rule) {
    s << rule->toString() << "\n";
    std::vector<Relation> rhRelations;
    for (Predicate* predicate : rule->getBodyPredicates()) {
        rhRelations.push_back(evaluatePredicate(predicate));
    }
    Relation relation = rhRelations.at(0);
    if (rhRelations.size() > 1) {
        for (unsigned int i = 1; i < rhRelations.size(); i++) {
            relation  = relation.naturalJoin(rhRelations.at(i));
        }
    }
    std::vector<unsigned int> indices;
    for (auto i : rule->getHeadPredicate()->getParameters()) {
        for (unsigned int j = 0; j < relation.getHeader().getAttributes().size(); j++) {
            if (i->getName() == relation.getHeader().getAttributes().at(j)) {
                indices.push_back(j);
            }
        }
    }

    relation = relation.project(indices);
    std::vector<std::string> attributeNames;
    for (auto param : rule->getHeadPredicate()->getParameters()) {
        attributeNames.push_back(param->getName());
    }
    relation.setName(rule->getHeadPredicate()->getName());
    relation.rename(attributeNames);
    s << database.getMap()[relation.getName()].relUnion(relation);
}





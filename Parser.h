//
// Created by bkweb on 9/29/2021.
//

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "iostream"
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Parameter.h"

class Parser {
private:
    unsigned int index;
    void parse();
    void parseDatalogProgram();
    void parseSchemeList();
    void parseFactList();
    void parseRuleList();
    void parseQueryList();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    void parseHeadPredicate();
    void parsePredicate();
    void parsePredicateList();
    void parseParameterList();
    void parseStringList();
    void parseIDList();
    void parseParameter();
    bool match(TokenType);
    bool success;
    std::vector<Token*> tokens;
    DatalogProgram dlProgram;
    Predicate *tempPredicate;
    Parameter *tempParameter;
    Rule *tempRule;

    // DatalogProgram parse();
public:
    Parser();
    Parser(const std::vector<Token*>&);
    ~Parser();

    std::string toString();
};


#endif //PARSER_H

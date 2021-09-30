//
// Created by bkweb on 9/29/2021.
//

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "iostream"
#include "Token.h"

class Parser {
private:
    unsigned int index;
    void parse();
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void predicate();
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    void parameter();
    bool match(TokenType);
    std::vector<Token*> tokens;
    // DatalogProgram parse();
public:
    Parser();
    Parser(const std::vector<Token*>&);
    ~Parser();

    std::string toString();
};


#endif //PARSER_H

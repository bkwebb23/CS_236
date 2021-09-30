//
// Created by bkweb on 9/29/2021.
//

#include "Parser.h"
#include "Token.h"
#include <sstream>


Parser::Parser() = default;
Parser::Parser(const std::vector<Token*>& tokens) {
    index = 0;
    this->tokens = tokens;
    parse();
}

void Parser::parse() {
    try {
        datalogProgram();
    } catch (Token* error) {
        std::cout << "Failure!\n\t" << error->toString();
    }
}

std::string Parser::toString() {
    std::stringstream s("Tokens");
    s << "This probably doesn't work yet";
    return s.str();
}

void Parser::datalogProgram() {
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    scheme();
    schemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    factList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    ruleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    query();
    queryList();
    match(TokenType::E_O_F);
}

void Parser::schemeList() {
    std::cout << "iteration\n";
    if (tokens.at(index)->getType() == TokenType::FACTS) {
        return;
    }
    else {
        scheme();
        schemeList();
    }
}

void Parser::factList() {

}

void Parser::ruleList() {

}

void Parser::queryList() {

}

void Parser::scheme() {

}

void Parser::fact() {

}

void Parser::rule() {

}

void Parser::query() {

}

void Parser::headPredicate() {

}

void Parser::predicate() {

}

void Parser::predicateList() {

}

void Parser::parameterList() {

}

void Parser::stringList() {

}

void Parser::idList() {

}

void Parser::parameter() {

}

bool Parser::match(TokenType expectedTokenType) {
    if (expectedTokenType == tokens.at(index)->getType()) {
        index++;
    } else {
        throw tokens.at(index);
    }
    return true;
}

Parser::~Parser() = default;

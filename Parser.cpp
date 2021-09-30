#include "Parser.h"
#include "Token.h"
#include <sstream>

Parser::Parser() = default;
Parser::Parser(const std::vector<Token*>& tokens) {
    index = 0;
    success = false;
    this->tokens = tokens;
    parse();
}

void Parser::parse() {
    try {
        parseDatalogProgram();
        success = true;
    } catch (Token* error) {
        std::cout << "Failure!\n  " << error->toString();
    } catch (const std::out_of_range& oor) {
        std::cout << "Failure!\n";
    }
}

std::string Parser::toString() {
    std::stringstream s;
    if (success) {
        s << "Success!";
    }
    return s.str();
}

void Parser::parseDatalogProgram() {
    match(TokenType::SCHEMES);
    match(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    match(TokenType::FACTS);
    match(TokenType::COLON);
    parseFactList();
    match(TokenType::RULES);
    match(TokenType::COLON);
    parseRuleList();
    match(TokenType::QUERIES);
    match(TokenType::COLON);
    parseQuery();
    parseQueryList();
    match(TokenType::E_O_F);
}

void Parser::parseSchemeList() {
    if (tokens.at(index)->getType() == TokenType::ID) {
        return;
    } else {
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseFactList() {
    if (tokens.at(index)->getType() == TokenType::RULES){
        return;
    } else {
        parseFact();
        parseFactList();
    }
}

void Parser::parseRuleList() {
    if (tokens.at(index)->getType() == TokenType::QUERIES){
        return;
    } else {
        parseRule();
        parseRuleList();
    }
}

void Parser::parseQueryList() {
    if (tokens.at(index)->getType() == TokenType::E_O_F) {
        return;
    } else {
        parseQuery();
        parseQueryList();
    }
}

void Parser::parseScheme() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parseFact() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::STRING);
    parseStringList();
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
}

void Parser::parseRule() {
    parseHeadPredicate();
    match(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(TokenType::PERIOD);
}

void Parser::parseQuery() {
    parsePredicate();
    match(TokenType::Q_MARK);
}

void Parser::parseHeadPredicate() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    match(TokenType::ID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicate() {
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    parseParameter();
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicateList() {
    if (tokens.at(index)->getType() == TokenType::PERIOD) {
        return;
    } else {
        match(TokenType::COMMA);
        parsePredicate();
        parsePredicateList();
    }
}

void Parser::parseParameterList() {
    if (tokens.at(index)->getType() == TokenType::RIGHT_PAREN) {
        return;
    } else {
        match(TokenType::COMMA);
        parseParameter();
        parseParameterList();
    }
}

void Parser::parseStringList() {
    if (tokens.at(index)->getType() == TokenType::RIGHT_PAREN) {
        return;
    } else {
        match(TokenType::COMMA);
        match(TokenType::STRING);
        parseStringList();
    }
}

void Parser::parseIDList() {
    if (tokens.at(index)->getType() == TokenType::RIGHT_PAREN){
        return;
    } else {
        match(TokenType::COMMA);
        match(TokenType::ID);
        parseIDList();
    }
}

void Parser::parseParameter() {
    if (tokens.at(index)->getType() == TokenType::STRING) {
        match(TokenType::STRING);
    } else {
        match(TokenType::ID);
    }
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

#include "Parser.h"
#include "Token.h"
#include <sstream>

Parser::Parser() = default;
Parser::Parser(const std::vector<Token*>& tokens) {
    index = 0;
    success = false;
    this->tempParameter = new Parameter();
    this->tempPredicate = new Predicate();
    this->tokens = tokens;
    parse();
}

void Parser::parse() {
    try {
        parseDatalogProgram();
        success = true;
    } catch (Token* errorToken) {
        std::cout << "Failure!\n  " << errorToken->toString();
    } catch (const std::out_of_range& oor) {
        std::cout << "Failure!\n";
    } catch (std::string genError) {
        std::cout << "Failure!\n  " << genError;
    }
}

std::string Parser::toString() {
    std::stringstream s;
    if (success) {
        s << "Success!\n";
    }
    s << dlProgram.toString();
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

void Parser::parseScheme() {
    tempPredicate = new Predicate(tokens.at(index)->getValue());
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::ID);
    tempPredicate->addParameter(tempParameter);
    match(TokenType::ID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
    dlProgram.addScheme(tempPredicate);
}

void Parser::parseSchemeList() {
    if (tokens.at(index)->getType() == TokenType::FACTS) {
        return;
    } else {
        parseScheme();
        parseSchemeList();
    }
}

void Parser::parseIDList() {
    if (tokens.at(index)->getType() == TokenType::RIGHT_PAREN){
        return;
    } else {
        match(TokenType::COMMA);
        tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::ID);
        tempPredicate->addParameter(tempParameter);
        match(TokenType::ID);
        parseIDList();
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

void Parser::parseFact() {
    tempPredicate = new Predicate(tokens.at(index)->getValue());
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::STRING);
    match(TokenType::STRING);
    tempPredicate->addParameter(tempParameter);
    parseStringList();
    match(TokenType::RIGHT_PAREN);
    match(TokenType::PERIOD);
    dlProgram.addFact(tempPredicate);
}

void Parser::parseRuleList() {
    if (tokens.at(index)->getType() == TokenType::QUERIES){
        return;
    } else {
        parseRule();
        parseRuleList();
    }
}

void Parser::parseRule() {
    parseHeadPredicate();
    match(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(TokenType::PERIOD);
}

void Parser::parseQueryList() {
    if (tokens.at(index)->getType() == TokenType::E_O_F) {
        return;
    } else {
        parseQuery();
        parseQueryList();
    }
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
        tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::STRING);
        tempPredicate->addParameter(tempParameter);
        match(TokenType::STRING);
        parseStringList();
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

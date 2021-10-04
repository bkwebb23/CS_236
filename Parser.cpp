#include "Parser.h"
#include <sstream>

Parser::Parser() = default;
Parser::Parser(const std::vector<Token*>& tokens) {
    index = 0;
    success = false;
    this->tempParameter = new Parameter();
    this->tempPredicate = new Predicate();
    this->tempRule = new Rule();
    this->tokens = tokens;
    parse(); // Immediately begin parsing token list
}

void Parser::parse() {
    // Check whether the given list of tokens forms a valid datalog program
    try {
        parseDatalogProgram();
        success = true;
    } catch (Token* errorToken) { // This should really be the only type of error that's ever thrown
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
        s << dlProgram.toString();
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
    tempRule = new Rule();
    tempPredicate = new Predicate();
    parseHeadPredicate();
    tempRule->setHeadPredicate(tempPredicate);
    match(TokenType::COLON_DASH);
    parsePredicate();
    parsePredicateList();
    match(TokenType::PERIOD);
    dlProgram.addRule(tempRule);
}

void Parser::parseHeadPredicate() {
    tempPredicate->setName(tokens.at(index)->getValue());
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::ID);
    tempPredicate->addParameter(tempParameter);
    match(TokenType::ID);
    parseIDList();
    match(TokenType::RIGHT_PAREN);
}

void Parser::parsePredicate() {
    tempPredicate = new Predicate(tokens.at(index)->getValue());
    match(TokenType::ID);
    match(TokenType::LEFT_PAREN);
    parseParameter();
    tempPredicate->addParameter(tempParameter);
    parseParameterList();
    match(TokenType::RIGHT_PAREN);
    if (tokens.at(index)->getType() == TokenType::PERIOD || tokens.at(index)->getType() == TokenType::COMMA) {
        tempRule->addBodyPredicate(tempPredicate);
    } else if (tokens.at(index)->getType() == TokenType::Q_MARK) {
        return;
    }
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

void Parser::parseParameter() {
    if (tokens.at(index)->getType() == TokenType::STRING) {
        tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::STRING);
        match(TokenType::STRING);
    } else {
        tempParameter = new Parameter(tokens.at(index)->getValue(), TokenType::ID);
        match(TokenType::ID);
    }
}

void Parser::parseParameterList() {
    if (tokens.at(index)->getType() == TokenType::RIGHT_PAREN) {
        return;
    } else {
        match(TokenType::COMMA);
        parseParameter();
        tempPredicate->addParameter(tempParameter);
        parseParameterList();
    }
}

void Parser::parseQuery() {
    parsePredicate();
    dlProgram.addQuery(tempPredicate);
    match(TokenType::Q_MARK);
}

void Parser::parseQueryList() {
    if (tokens.at(index)->getType() == TokenType::E_O_F) {
        return;
    } else {
        parseQuery();
        parseQueryList();
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

bool Parser::match(TokenType expectedTokenType) {
    if (expectedTokenType == tokens.at(index)->getType()) {
        // If the token type in the input vector matches the type expected by the grammar,
        //      increment the index to consume that token
        index++;
    } else {
        throw tokens.at(index);
    }
    return true;
}

Parser::~Parser() = default;

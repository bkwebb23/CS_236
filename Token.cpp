#include <sstream>
#include <iostream>
#include <utility>
#include "Token.h"

using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    this->line = line;
    this->description = std::move(description);
    this->type = type;
    tokenName(type);
}

TokenType Token::getType() const {
    return type;
}

string Token::toString() {
    stringstream s("");
    s << "(" << tokenName(type) << ",\"" << this->description << "\"," <<
        to_string(line) << ")";
    return s.str();
}

std::string Token::tokenName(TokenType name) {
    if (name == TokenType::COLON){
        return "COLON";
    } else if (name == TokenType::COLON_DASH) {
        return "COLON_DASH";
    } else if (name == TokenType::COMMA) {
        return "COMMA";
    } else if (name == TokenType::PERIOD) {
        return "PERIOD";
    } else if (name == TokenType::Q_MARK) {
        return "Q_MARK";
    } else if (name == TokenType::LEFT_PAREN) {
        return "LEFT_PAREN";
    } else if (name == TokenType::RIGHT_PAREN) {
        return "RIGHT_PAREN";
    } else if (name == TokenType::MULTIPLY) {
        return "MULTIPLY";
    } else if (name == TokenType::ADD) {
        return "ADD";
    } else if (name == TokenType::SCHEMES) {
        return "SCHEMES";
    } else if (name == TokenType::FACTS) {
        return "FACTS";
    } else if (name == TokenType::RULES) {
        return "RULES";
    } else if (name == TokenType::QUERIES) {
        return "QUERIES";
    } else if (name == TokenType::ID) {
        return "ID";
    } else if (name == TokenType::STRING) {
        return "STRING";
    } else if (name == TokenType::COMMENT) {
        return "COMMENT";
    } else if (name == TokenType::E_O_F) {
        return "EOF";
    } else if (name == TokenType::UNDEFINED) {
        return "UNDEFINED";
    }
    return "Error! Token not recognized (or undefined)";
}

std::string Token::getValue() {
    return description;
}



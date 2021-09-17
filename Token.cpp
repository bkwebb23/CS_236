#include <sstream>
#include <iostream>
#include "Token.h"

using namespace std;

Token::Token(TokenType type, std::string description, int line) {
    this->line = line;
    this->description = description;
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

std::string Token::tokenName(TokenType type) {
    if (type == TokenType::COLON){
        return "COLON";
    } else if (type == TokenType::COLON_DASH) {
        return "COLON_DASH";
    } else if (type == TokenType::COMMA) {
        return "COMMA";
    } else if (type == TokenType::PERIOD) {
        return "PERIOD";
    } else if (type == TokenType::Q_MARK) {
        return "Q_MARK";
    } else if (type == TokenType::LEFT_PAREN) {
        return "LEFT_PAREN";
    } else if (type == TokenType::RIGHT_PAREN) {
        return "RIGHT_PAREN";
    } else if (type == TokenType::MULTIPLY) {
        return "MULTIPLY";
    } else if (type == TokenType::ADD) {
        return "ADD";
    } else if (type == TokenType::SCHEMES) {
        return "SCHEMES";
    } else if (type == TokenType::FACTS) {
        return "FACTS";
    } else if (type == TokenType::RULES) {
        return "RULES";
    } else if (type == TokenType::QUERIES) {
        return "QUERIES";
    } else if (type == TokenType::ID) {
        return "ID";
    } else if (type == TokenType::STRING) {
        return "STRING";
    } else if (type == TokenType::COMMENT) {
        return "COMMENT";
    } else if (type == TokenType::E_O_F) {
        return "EOF";
    } else if (type == TokenType::UNDEFINED) {
        return "UNDEFINED";
    }
    return "Error! Token not recognized (or undefined)";
}



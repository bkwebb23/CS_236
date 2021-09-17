//
// Created by bkweb on 9/16/2021.
//

#include "MatcherAutomaton.h"

void MatcherAutomaton::S0(const std::string& input) {
    bool isMatch = true;
    inputRead = 0;  // member variable inherited from Automaton class
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = toMatch.size();
    }
}

MatcherAutomaton::MatcherAutomaton(std::string toMatch) {
    this->toMatch = toMatch;
}

Token *MatcherAutomaton::CreateToken(std::string input, int lineNumber) {
    if (toMatch == ".") {
        type = TokenType::PERIOD;
    } else if (toMatch == ",") {
        type = TokenType::COMMA;
    } else if (toMatch == "?") {
        type = TokenType::Q_MARK;
    } else if (toMatch == "(") {
        type = TokenType::LEFT_PAREN;
    } else if (toMatch == ")") {
        type = TokenType::RIGHT_PAREN;
    } else if (toMatch == "*") {
        type = TokenType::MULTIPLY;
    } else if (toMatch == "+") {
        type = TokenType::ADD;
    } else if (toMatch == "Schemes") {
        type = TokenType::SCHEMES;
    } else if (toMatch == "Facts") {
        type = TokenType::FACTS;
    } else if (toMatch == "Rules") {
        type = TokenType::RULES;
    } else if (toMatch == "Queries") {
        type = TokenType::QUERIES;
    }
    return new Token(type, input.substr(0, inputRead), lineNumber);
}

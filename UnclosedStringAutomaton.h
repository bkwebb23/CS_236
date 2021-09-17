//
// Created by bkweb on 9/16/2021.
//

#ifndef PROJECT_1_UNCLOSEDSTRINGAUTOMATON_H
#define PROJECT_1_UNCLOSEDSTRINGAUTOMATON_H

#include "Automaton.h"

class UnclosedStringAutomaton : public Automaton {
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
public:
    UnclosedStringAutomaton() : Automaton(TokenType::UNDEFINED) {}  // Call the base constructor
    void S0(const std::string& input);
};


#endif //PROJECT_1_UNCLOSEDSTRINGAUTOMATON_H

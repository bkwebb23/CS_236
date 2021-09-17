//
// Created by bkweb on 9/16/2021.
//

#ifndef PROJECT_1_MATCHERAUTOMATON_H
#define PROJECT_1_MATCHERAUTOMATON_H

#include "Automaton.h"

class MatcherAutomaton : public Automaton {
private:
    std::string toMatch;
public:
    MatcherAutomaton(std::string toMatch);
    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber);
};


#endif //PROJECT_1_MATCHERAUTOMATON_H

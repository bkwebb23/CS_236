//
// Created by bkweb on 9/16/2021.
//

#ifndef PROJECT_1_E_O_FAUTOMATON_H
#define PROJECT_1_E_O_FAUTOMATON_H

#include "Automaton.h"

class E_O_FAutomaton : public Automaton {
public:
    E_O_FAutomaton() : Automaton(TokenType::E_O_F) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_E_O_FAUTOMATON_H

//
// Created by bkweb on 9/16/2021.
//

#include "StringAutomaton.h"
void StringAutomaton::S0(const std::string& input) {
    if (input[0] == '\'') {
        inputRead++;
        S1(input.substr(inputRead));
    } else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string &input) {
    index = 0;
    while (input[index] != '\'' && !input.substr(index).empty()) {
        index++;
        inputRead++;
    }
    if (input.substr(index).empty()) {
        inputRead = 0;
    } else if (input[index] == '\'') {
        inputRead++;
        index++;
        if (!input.substr(index).empty() && input[index] == '\'') {
            inputRead++;
            index++;
            S2(input.substr(index));
        }
    }
}


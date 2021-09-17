//
// Created by bkweb on 9/16/2021.
//

#include "StringAutomaton.h"
void StringAutomaton::S0(const std::string& input) {
    if (input[0] == '\'' && input.size() > 1) {
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
        Serr();
    } else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input.substr(index));
    }
}

void StringAutomaton::S2(const std::string &input) {
    index = 0;
    if (input.size() > 1){
        if(input[index] == '\'') {
            inputRead++;
            index++;
            S1(input.substr(index));
        }
    }
}


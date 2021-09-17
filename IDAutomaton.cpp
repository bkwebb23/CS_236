//
// Created by bkweb on 9/16/2021.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    index = 0;
    if (std::isalpha(input[index]) && input.size() > 1) {
        index++;
        inputRead++;
        S1(input.substr(index));
    } else if (std::isalpha(input[index])) {
        index++;
        inputRead++;
    } else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string &input) {
    index = 0;
    while(input.size() > 0 && (std::isalnum(input[index]))){
        index++;
        inputRead++;
    }
}

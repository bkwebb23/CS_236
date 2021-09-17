//
// Created by bkweb on 9/16/2021.
//

#include "UnclosedStringAutomaton.h"
void UnclosedStringAutomaton::S0(const std::string& input) {
    if (!input.empty() && input[0] == '\'') {
        inputRead++;
        index++;
        S1(input.substr(index));
    } else {
        Serr();
    }
}

void UnclosedStringAutomaton::S1(const std::string &input) {
    index = 0;
    while (input[index] != '\'' && !input.substr(index).empty()) {
        index++;
        inputRead++;
        if (input[index] == '\n'){
            newLines++;
        }
    }
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input.substr(index));
    }
}

void UnclosedStringAutomaton::S2(const std::string &input) {
    index = 0;
    if ((input.empty())| (input[0] != '\'')) {
        Serr();
    } else {
        index++;
        inputRead++;
        S1(input.substr(index));
    }
}
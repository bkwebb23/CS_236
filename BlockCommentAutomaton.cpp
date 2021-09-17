//
// Created by bkweb on 9/16/2021.
//

#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0(const std::string &input) {
    if(!input.empty() && input[index] == '#') {
        index++;
        inputRead++;
        S1(input);
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string &input) {
    if(!input.substr(index).empty() && input[index] == '|') {
        index++;
        inputRead++;
        S2(input);
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S2(const std::string &input) {
    while (!input.substr(index).empty() && input[index] != '|') {
        if (input[index] == '\n') {
            newLines++;
        }
        index++;
        inputRead++;
    }
    if (!input.substr(index).empty()) {
        index++;
        inputRead++;
        S3(input);
    }
}

void BlockCommentAutomaton::S3(const std::string &input) {
    if (!input.substr(index).empty() && input[index] != '#') {
        index++;
        inputRead++;
        S2(input);
    } else if (!input.substr(index).empty()){
        index++;
        inputRead++;
    }
}

//
// Created by bkweb on 9/16/2021.
//

#include "UnclosedCommentAutomaton.h"
void UnclosedCommentAutomaton::S0(const std::string &input) {
    if(!input.empty() && input[0] == '#'){
        index++;
        inputRead++;
        S1(input.substr(index));
    } else {
        Serr();
    }
}

void UnclosedCommentAutomaton::S1(const std::string &input) {
    if(!input.empty() && input[0] == '|'){
        index++;
        inputRead++;
        S2(input.substr(index));
    } else {
        Serr();
    }
}

void UnclosedCommentAutomaton::S2(const std::string &input) {
    while (!input.substr(index).empty() && input[index] != '|') {
        if (input[index] == '\n') {
            newLines++;
        }
        index++;
        inputRead++;
    }
    if (!input.substr(index).empty() && input[index] == '|') {
        index++;
        inputRead++;
        S3(input.substr(index));
    }
}

void UnclosedCommentAutomaton::S3(const std::string& input) {
    if(!input.empty() && input[0] == '#'){
        Serr();
    } else if (!input.empty()){
        index++;
        inputRead++;
        S2(input.substr(index));
    }
}
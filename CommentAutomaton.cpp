//
// Created by bkweb on 9/16/2021.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
}
void CommentAutomaton::S1(const std::string& input) {
    while (!input.substr(index).empty()) {
        if (input[index] == '\n') {
            break;
        }
        else {
            inputRead++;
            index++;
        }
    }

}

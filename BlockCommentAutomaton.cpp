//
// Created by bkweb on 9/16/2021.
//

#include "BlockCommentAutomaton.h"
void BlockCommentAutomaton::S0(const std::string& input) {
    if ((input[0] == '#') && (input.size() > 3)) {
        index++;
        inputRead++;
        S1(input.substr(index));
    } else {
        Serr();
    }
}
void BlockCommentAutomaton::S1(const std::string& input) {
    if(input[0]=='|' && input.size() > 2){
        index++;
        inputRead++;
        S2(input.substr(index));
    } else {
        Serr();
    }
}
void BlockCommentAutomaton::S2(const std::string& input) {
    while (input.size() > 1){
        if(input[0] == '|'){
            index++;
            inputRead++;
            S4(input.substr(index));
        }
    }
    Serr();
}
void BlockCommentAutomaton::S4(const std::string& input) {
    if (input.empty()) {
        Serr();
    } else if (input[0] == '#') {
        index++;
        inputRead++;
    } else {
        index++;
        inputRead++;
        S2(input.substr(index));
    }
}

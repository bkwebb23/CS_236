//
// Created by bkweb on 9/16/2021.
//

#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0(const std::string &input) {
    // First character of nonempty input must be #
    //      if so, move to S1
    if(!input.empty() && input[index] == '#') {
        index++;
        inputRead++;
        S1(input);
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string &input) {
    // Second character of nonempty input must be |
    //      if so, move to S2
    if(!input.substr(index).empty() && input[index] == '|') {
        index++;
        inputRead++;
        S2(input);
    } else {
        Serr();
    }
}

//  I'm not sure why I have index++ as often as I do in this function, but it works
void BlockCommentAutomaton::S2(const std::string &input) {
    // Continues consuming characters until either EOF or '|' is reached
    while (!input.substr(index).empty() && input[index] != '|') {
        if (input[index] == '\n') {
            newLines++;
        }
        index++;
        inputRead++;
    }
    if (!input.substr(index).empty()) {
        // If EOF wasn't reached, increment and move to S3
        index++;
        inputRead++;
        S3(input);
    } else {
        // EOF was reached before end of block comment; reject input
        Serr();
    }
}

void BlockCommentAutomaton::S3(const std::string &input) {
    if (!input.substr(index).empty() && input[index] != '#') {
        // If character immediately after '|' isn't EOF or #, increment and move to S2
        index++;
        inputRead++;
        S2(input);
    } else if (!input.substr(index).empty()){
        // If character immmediately after '|' is '#', increment and end
        index++;
        inputRead++;
    } else {
        // EOF was reached before end of block comment; reject input
        Serr();
    }
}

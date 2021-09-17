//
// Created by bkweb on 9/16/2021.
//

#include "BlockCommentAutomaton.h"
//void BlockCommentAutomaton::S0(const std::string& input) {
//    index = 0;
//    if ((input[0] == '#') && (input.size() > 3)) {
//        index++;
//        inputRead++;
//        std::string input2 = input.substr(1);
//        S1(input2);
////        S1(input.substr(index));
//    } else {
//        Serr();
//    }
//}
//void BlockCommentAutomaton::S1(const std::string& input) {
//    index = 0;
//    if(!input.empty() && input[0]=='|'){
//        index++;
//        inputRead++;
//        std::string input2 = input.substr(1);
//        S2(input2);
////        S2(input.substr(index));
//    } else {
//        Serr();
//    }
//}
//void BlockCommentAutomaton::S2(const std::string& input) {
//    index = 0;
//    while (input.size() > 1){
//        if(input[0] == '|'){
//            index++;
//            inputRead++;
//            std::string input2 = input.substr(1);
//            S4(input2);
////            S4(input.substr(index));
//        }
//    }
//    Serr();
//}
//void BlockCommentAutomaton::S4(const std::string& input) {
//    index = 0;
//    if (input.empty()) {
//        Serr();
//    } else if (input[0] == '#') {
//        index++;
//        inputRead++;
//    } else {
//        index++;
//        inputRead++;
//        std::string input2 = input.substr(1);
//        S2(input2);
////        S2(input.substr(index));
//    }
//}

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

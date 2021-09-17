#include <sstream>
#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommentAutomaton.h"
#include "E_O_FAutomaton.h"

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
    input = "";
}

Lexer::Lexer(string inFile) {
    this->input = inFile;
    CreateAutomata();
    this->Run(input);
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommentAutomaton());
    // TODO: Add the other needed automata here
    automata.push_back(new E_O_FAutomaton());
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    unsigned int lineNumber = 1;
    while (!input.empty()) {
        unsigned int maxRead = 0;
        unsigned int maxAutomaton = 0;
        while(!input.empty() && isspace(input[0])) {
            if (input[0] == '\n') {
                lineNumber++;
            }
            input = input.substr(1);
        }
        if (input.empty()) break;
        for (unsigned int i =0; i < automata.size(); i++) {
            unsigned int inputRead = 0;
            inputRead = automata.at(i)->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = i;
            }
        }
        if (maxRead > 0) {
            Token* newToken = automata.at(maxAutomaton)->CreateToken(input, lineNumber);
            lineNumber += automata.at(maxAutomaton)->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            // set newToken to a  new undefined Token
            // (with first character of input)
            //add newToken to collection of all token
        }
        input = input.substr(maxRead);
        // Update `input` by removing characters read to create Token
        // remove maxRead characters from input
    }
    Token* newToken = automata.back()->CreateToken(input, lineNumber);
    lineNumber += automata.back()->NewLinesRead();
    tokens.push_back(newToken);
    // add end of file token to all tokens


    // PSEUDOCODE
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace in between tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */
}

string Lexer::toString() {
    stringstream s("Tokens");
    for(unsigned int i = 0; i < tokens.size(); i++) {
        s << tokens.at(i)->toString() << "\n";
    }
    s << "Total Tokens = " << to_string(tokens.size());
    return s.str();
}

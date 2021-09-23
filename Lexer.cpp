#include <sstream>
#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommentAutomaton.h"
#include "E_O_FAutomaton.h"
#include "MatcherAutomaton.h"
#include "StringAutomaton.h"
#include "IDAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "UnclosedStringAutomaton.h"
#include "UnclosedCommentAutomaton.h"

using namespace std;

Lexer::Lexer() {
    CreateAutomata();
    fin = "";
}

Lexer::Lexer(string inFile) {
    this->fin = inFile;
    CreateAutomata();
    this->Run(fin);
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new UnclosedCommentAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MatcherAutomaton("."));
    automata.push_back(new MatcherAutomaton(","));
    automata.push_back(new MatcherAutomaton("?"));
    automata.push_back(new MatcherAutomaton("("));
    automata.push_back(new MatcherAutomaton(")"));
    automata.push_back(new MatcherAutomaton("*"));
    automata.push_back(new MatcherAutomaton("+"));
    automata.push_back(new MatcherAutomaton("Schemes"));
    automata.push_back(new MatcherAutomaton("Queries"));
    automata.push_back(new MatcherAutomaton("Facts"));
    automata.push_back(new MatcherAutomaton("Rules"));
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new UnclosedStringAutomaton());
    automata.push_back(new E_O_FAutomaton());
}

void Lexer::Run(std::string& input) {

    unsigned int lineNumber = 1;

    /* While there are more characters to tokenize */
    while (!input.empty()) {
        unsigned int maxRead = 0;   //  Set number of characters in input string to 0
        unsigned int maxAutomaton = 0;  // Set max automaton to the first automaton in automata

        /* Checks for whitespace and increments the line number counter as necessary */
        while(!input.empty() && isspace(input[0])) {
            if (input[0] == '\n') {
                lineNumber++;
            }
            input = input.substr(1);
        }

        if (input.empty()) break; // Ends loop if end-of-file is reached

        /* Runs the input string on each FSA, and the index of the FSA that accepts the largest portion of the
         * input string is assigned to 'maxAutomaton'. The number of characters accepted by that FSA is
         * assigned to 'maxRead'.*/
        for (unsigned int i =0; i < automata.size(); i++) {
            unsigned int inputRead = 0;
            inputRead = automata.at(i)->Start(input);
            if (i == 0 && inputRead > 0) {
                maxRead = inputRead;
                maxAutomaton = i;
                break;
            }
            if (inputRead > maxRead) { // If given FSA read the most number of characters, store inputRead to maxRead
                maxRead = inputRead;
                maxAutomaton = i;
            }
        }
        if (maxRead > 0) { // Tokenize based off of whichever FSA accepted the most characters
            Token* newToken = automata.at(maxAutomaton)->CreateToken(input, lineNumber);
            lineNumber += automata.at(maxAutomaton)->NewLinesRead();
            tokens.push_back(newToken);
        }
        else { // If no FSA accepted, create UNDEFINED token (this is, perhaps, obsolete?)
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
            tokens.push_back(newToken);
        }

        // Update `input` by removing characters read to create Token
        input = input.substr(maxRead);
    }

    // add end of file token to all tokens
    Token* newToken = automata.back()->CreateToken(input, lineNumber);
    lineNumber += automata.back()->NewLinesRead();
    tokens.push_back(newToken);
}

string Lexer::toString() {
    stringstream s("Tokens");
    for(unsigned int i = 0; i < tokens.size(); i++) {
        s << tokens.at(i)->toString() << "\n";
    }
    s << "Total Tokens = " << to_string(tokens.size());
    return s.str();
}

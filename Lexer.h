#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <string>
#include "Automaton.h"
#include "Token.h"

using namespace std;

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    std::string fin;
    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer(string inFile);
    Lexer();
    ~Lexer();

    void Run(std::string& instring);
    string toString();
    
    // TODO: add other public methods here

};

#endif // LEXER_H


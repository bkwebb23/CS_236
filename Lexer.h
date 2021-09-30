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

public:
    explicit Lexer(string inFile);
    Lexer();
    ~Lexer();

    const vector<Token *> &getTokens() const;
    void Run(std::string& instring);
    string toString();
};

#endif // LEXER_H


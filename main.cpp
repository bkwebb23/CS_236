#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {

    // check command line arguments
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    // open file
    string fileName = argv[1];
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cout << "File " << fileName << " could not be found or opened." << endl;
        return 1;
    }

    string input((std::istreambuf_iterator<char>(inFile)),
             (std::istreambuf_iterator<char>()));

    Lexer* lexer = new Lexer(input);

    // Select tokens from input file
    vector<Token*> tokens = lexer->getTokens();

    // Remove comment tokens from input file
    vector<Token*> tokensWOComments;
    for (unsigned int i= 0; i < tokens.size(); i++) {
        if (tokens.at(i)->getType() != TokenType::COMMENT) {
            tokensWOComments.push_back(tokens.at(i));
        }
    }

    // Parse through token sequence to determine if the datalog syntax is valid
    Parser* parser = new Parser(tokensWOComments);
    cout << parser->toString();



    delete lexer;
    delete parser;

    return 0;
}
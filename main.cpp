#include <fstream>
#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Interpreter.h"

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

    auto* lexer = new Lexer(input);

    // Select tokens from input file
    vector<Token*> tokens = lexer->getTokens();

    // Remove comment tokens from input file
    vector<Token*> tokensWOComments;
    for (auto & token : tokens) {
        if (token->getType() != TokenType::COMMENT) {
            tokensWOComments.push_back(token);
        }
    }

    // Parse through token sequence to determine if the datalog syntax is valid
    auto* parser = new Parser(tokensWOComments);

    DatalogProgram datalogProgram = parser->getDlProgram();

    auto* interpreter = new Interpreter(datalogProgram);

    cout << interpreter->toString();
    cout << input;


    delete lexer;
    delete parser;
    delete interpreter;

    return 0;
}
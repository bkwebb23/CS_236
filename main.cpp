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

    //cout << lexer->toString() << "\n";

    vector<Token*> tokens = lexer->getTokens();
    Parser* parser = new Parser(tokens);
    cout << parser->toString() << "\n";

    delete lexer;

    return 0;
}
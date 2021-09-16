#include <fstream>
#include <iostream>
#include <string>
#include "Lexer.h"

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

    cout << argv[0] << "\n" << "test\n" << argv[1] << "\n";

    string input((std::istreambuf_iterator<char>(inFile)),
             (std::istreambuf_iterator<char>()));

    Lexer* lexer = new Lexer(input);

    cout << lexer->toString();

    delete lexer;

    return 0;
}
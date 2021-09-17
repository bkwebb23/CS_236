#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum class TokenType {
    COLON,
    COLON_DASH,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    E_O_F,
    UNDEFINED
}; // don't forget to include EOF

class Token
{
private:
    std::string description;
    TokenType type;
    int line;// TODO: add member variables for information needed by Token
    std::string tokenName(TokenType name);

public:
    Token(TokenType type, std::string description, int line);
    std::string toString();

    TokenType getType() const;
    // TODO: add other needed methods
};

#endif // TOKEN_H


#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include "Token.h"

class Parameter {
private:
    TokenType type;
    std::string name;

public:
    Parameter();
    Parameter(std::string id, TokenType givenType);
    ~Parameter();

    TokenType getType() const;
    void setType(TokenType givenType);
    const std::string &getName() const;
    void setName(const std::string &id);

    std::string toString();
};


#endif //PARAMETER_H

#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"
#include "Token.h"

class Predicate {
private:
    std::string name;
    std::vector<Parameter*> parameters;

public:
    Predicate();
    Predicate(std::string id);
    ~Predicate();

    const std::string &getName() const;
    void setName(const std::string &id);
    const std::vector<Parameter*> &getParameters() const;
    void addParameter(Parameter* parameter);

    std::string toString();
};


#endif //PREDICATE_H

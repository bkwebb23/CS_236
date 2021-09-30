//
// Created by bkweb on 9/30/2021.
//

#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string name;
    std::vector<Parameter*> parameters;

public:
    Predicate();
    ~Predicate();

    const std::string &getName() const;
    void setName(const std::string &name);
    const std::vector<Parameter *> &getParameters() const;
    void setParameters(const std::vector<Parameter *> &parameters);
    void addParameter(Parameter* parameter);

    std::string toString();
};


#endif //PREDICATE_H

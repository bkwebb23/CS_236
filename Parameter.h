//
// Created by bkweb on 9/30/2021.
//

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter {
private:
    std::string name;
public:
    Parameter();
    ~Parameter();

    const std::string &getName() const;
    void setName(std::string &id);
};


#endif //PARAMETER_H

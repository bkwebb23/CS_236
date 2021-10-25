//
// Created by bkweb on 10/15/2021.
//

#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {
private:
    std::vector<std::string> values;

public:
    Tuple();
    ~Tuple();

    const std::vector<std::string> &getValues() const;
    std::string toString();
};


#endif //TUPLE_H

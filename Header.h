//
// Created by bkweb on 10/15/2021.
//

#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> attributes;

public:
    Header();
    Header(const std::vector<std::string> &attributes);
    ~Header();

    const std::vector<std::string> &getAttributes() const;
};


#endif //HEADER_H

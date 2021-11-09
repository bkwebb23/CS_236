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
    ~Header();

    const std::vector<std::string> &getAttributes() const;
    unsigned int attributeIndex(std::string attribute) const;
    void addAttribute(const std::string& attribute);
    void renameAttribute(unsigned int index, std::string name);


};


#endif //HEADER_H

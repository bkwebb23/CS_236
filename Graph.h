//
// Created by bkweb on 11/29/2021.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>
#include <sstream>
#include "Rule.h"

class Graph {
private:
    std::map<int, std::set<int>> adjList;

public:
    Graph();
    explicit Graph(std::map<int, std::set<int>>);
    explicit Graph(std::vector<Rule*> rules);
    virtual ~Graph();

    std::string toString();
    Graph reverseGraph();

    void addNode(int);

};


#endif //GRAPH_H

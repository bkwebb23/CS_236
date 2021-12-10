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
    std::map<int, std::set<int>> reversedList;
    std::map<int, bool> visited;
    std::vector<int> postorder;
    std::vector<std::set<int>> SCCs;

public:
    Graph();
    explicit Graph(std::vector<Rule*> rules);
    virtual ~Graph();

    std::string toString();
    std::map<int, std::set<int>> makeReversedList();
    void dfsPostorder(int root);
    void dfsForestPostorder();
    std::set<int> dfs(std::set<int>& tree, int root);
    void dfsForest();

    void addNode(int);
    std::vector<int> getPostorder();
    std::vector<std::set<int>> getSCCS();

};


#endif //GRAPH_H

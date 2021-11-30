//
// Created by bkweb on 11/29/2021.
//

#include "Graph.h"

Graph::Graph(std::vector<Rule*> rules) {
    std::map<std::string, int> ruleNames;
    for (unsigned int i = 0; i < rules.size(); i++) {
        adjList[i] = std::set<int>();
    }
    for (unsigned int i = 0; i < rules.size(); i++) {
        for (unsigned int j = 0; j < rules.at(i)->getBodyPredicates().size(); j++) {
            for (unsigned int k = 0; k < rules.size(); k++) {
                if (rules.at(k)->getHeadPredicate()->getName() == rules.at(i)->getBodyPredicates().at(j)->getName()) {
                    adjList[i].insert(k);
                }
            }
        }
    }
}

Graph::Graph(std::map<int, std::set<int>> mymap) {
    adjList = mymap;
}

Graph::Graph() {

}

std::string Graph::toString() {
    std::stringstream s("");
    s << "Dependency Graph\n";
    for (const auto& entry : adjList) {
        s << "R" << std::to_string(entry.first) << ":";
        bool first = true;
        for (auto node : entry.second) {
            if (!first) {
                s << ",";
            }
            s << "R" << std::to_string(node);
            first = false;
        }
        s << "\n";
    }
    s << "\n";
    return s.str();
}

Graph Graph::reverseGraph() {
    std::map<int, std::set<int>> reversedAdjList = std::map<int, std::set<int>>();
    for (const auto& it : adjList) {
        reversedAdjList[it.first] = std::set<int>();
    }
    for (const auto& mapit1 : adjList) {
        for (const auto& setit : mapit1.second) {
            for (auto& mapit2 : reversedAdjList) {
                if (setit == mapit2.first) {
                    mapit2.second.insert(setit); // NOT WORKING
                }
            }
        }
    }
    return Graph(reversedAdjList);
}

void Graph::addNode(int i) {
    adjList[i] = std::set<int>();
}


Graph::~Graph() = default;

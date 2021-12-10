//
// Created by bkweb on 11/29/2021.
//

#include "Graph.h"
#include <algorithm>

Graph::Graph(std::vector<Rule*> rules) {
    // Loop through rules and initialize the left-side of the adjacency lists
    for (unsigned int i = 0; i < rules.size(); i++) {
        adjList[i] = std::set<int>();
        visited[i] = false;
    }

    // For each rule i, we check to see if any other rule k consumes the jth body predicate of i. If so, we add k
    //      to the right side of the adjacency list at i
    for (unsigned int i = 0; i < rules.size(); i++) {
        for (unsigned int j = 0; j < rules.at(i)->getBodyPredicates().size(); j++) {
            for (unsigned int k = 0; k < rules.size(); k++) {
                if (rules.at(k)->getHeadPredicate()->getName() == rules.at(i)->getBodyPredicates().at(j)->getName()) {
                    adjList[i].insert(k);
                }
            }
        }
    }

    // Initializes the reverse adjacency list
    reversedList = makeReversedList();

    // Creates the postorder for the reversed graph
    dfsForestPostorder();

    // Creates the SCCs for the graph by doing repeatedly doing depth-first searches in the reverse postorder
    dfsForest();
}

Graph::Graph() = default;

std::string Graph::toString() { //          Outputs only the initial dependency graph
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

std::map<int, std::set<int>> Graph::makeReversedList() {
    std::map<int, std::set<int>> reversedAdjList = std::map<int, std::set<int>>();

    // Initializes the left side of the reversed adjacency list (same as left side of the original)
    for (const auto& it : adjList) {
        reversedAdjList[it.first] = std::set<int>();
    }

    // For each rule in both the reversed and original adjacency lists, if a rule in the reversed list ever appears
    //      on the right side of a rule in the original, we add the original rule to the right side of the reversed
    //      list rule
    for (auto& node : reversedAdjList) {
        for (const auto& ogNode : adjList) {
            if (ogNode.second.count(node.first) != 0) {
                node.second.insert(ogNode.first);
            }
        }
    }

    // Stores the reversed adjacency list as a private data member
    reversedList = reversedAdjList;
    return reversedAdjList;

}

void Graph::addNode(int i) {
    adjList[i] = std::set<int>();
}


void Graph::dfsPostorder(int root) {
    // Mark root node as visited
    visited[root] = true;

    // For each node that hasn't been visited along the way, continue the depth-first search
    for (auto& vertex : reversedList[root]){
        if (!visited[vertex]) {
            dfsPostorder(vertex);
        }
    }

    // Once all descendant nodes have been marked, we return to the parent node and add the root to our postorder list
    postorder.push_back(root);
}

void Graph::dfsForestPostorder() {
    // Clear existing graph
    for (auto&node : visited) {
        node.second = false;
    }
    // For each node that hasn't yet been visited, perform a depth-first search on it, marking visited nodes
    for (auto& node: visited) {
        if (!node.second) {
            dfsPostorder(node.first);
        }
    }
}

std::vector<int> Graph::getPostorder() {
    return postorder;
}

std::set<int> Graph::dfs(std::set<int>& tree, int root) {
    visited[root] = true;
    tree.insert(root);
    for (auto& vertex : adjList[root]) {
        if (!visited[vertex]) {
            dfs(tree,vertex);
        }
    }
    return tree;
}

void Graph::dfsForest() {
    SCCs = std::vector<std::set<int>>();
    for (auto& node : visited) {
        node.second = false;
    }
    std::vector<int> reversedPostorder = postorder;
    std::reverse(reversedPostorder.begin(), reversedPostorder.end());
    for (auto& value : reversedPostorder) {
        if (!visited[value]) {
            std::set<int> tree = std::set<int>();
            tree = dfs(tree, value);
            SCCs.push_back(tree);
        }
    }
}

std::vector<std::set<int>> Graph::getSCCS() {
    return SCCs;
}


Graph::~Graph() = default;

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>

class Node;
typedef std::set<Node*>::const_iterator node_iterator;

class Node {
    std::string name;
    std::set<Node*> neighbours;
    void addNeighbour(Node* neighbour);
    void removeNeighbour(Node* neighbour);
public:
    Node(const std::string& aname) : name(aname) {}
    const std::string& getName() const { return name; }
    node_iterator nb_begin() const { return neighbours.begin(); }
    node_iterator nb_end() const { return neighbours.end(); }
    friend class Graph;
};

class Graph {
    std::set<Node*> nodes;
public:
    Graph() {}
    Graph(const char* file_name);
    ~Graph();

    void addNode(Node* node);
    void removeNode(Node* node);
    void addEdge(Node* begin, Node* end);
    void removeEdge(Node* begin, Node* end);

    Node* findNode(const std::string& name) const;
    node_iterator begin() const { return nodes.begin(); }
    node_iterator end() const { return nodes.end(); }
    int size() const { return (int)nodes.size(); }

    void saveToFile(const char* file_name) const;
};

class BFS {
    const Graph& graph;
public:
    BFS(const Graph& agraph) : graph(agraph) {}
    bool connected(Node* begin, Node* end);
    void findComponent(Node* begin, std::set<Node*>& used, std::set<Node*>& comp);
};

#endif

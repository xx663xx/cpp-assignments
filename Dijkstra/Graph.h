#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>

class Node;

typedef std::vector<Node*>::const_iterator node_iterator;

class Node {
    int name;
    std::vector<Node*> nodes;
    std::vector<int> weights;
public:
    Node(int aname = 0);
    int getName() const;
    void addEdge(Node* node, int weight);
    int getWeight(Node* node) const;
    node_iterator nb_begin() const;
    node_iterator nb_end() const;
};

class Graph {
    std::vector<Node*> nodes;
public:
    Graph();
    ~Graph();
    Node* getNode(int name);
    void addNode(Node* node);
    void addEdge(int begin, int end, int weight);
    node_iterator begin() const;
    node_iterator end() const;
};

struct MarkedNode {
    Node* node;
    int mark;
    Node* prev;

    MarkedNode(Node* anode = 0, int amark = 0, Node* aprev = 0);
};

class PriorityQueue {
    std::vector<MarkedNode> nodes;
public:
    MarkedNode pop();
    void push(Node* node, int mark, Node* prev);
    bool empty() const;
};

struct Way {
    std::vector<Node*> nodes;
    int length;

    Way();
};

class Dijkstra {
    const Graph& graph;
    Way unroll(std::map<Node*, MarkedNode> visited, Node* begin, Node* curr);
public:
    Dijkstra(const Graph& agraph);
    Way shortestWay(Node* begin, Node* end);
};

#endif

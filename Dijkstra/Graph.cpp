#include "Graph.h"

Node::Node(int aname) {
    name = aname;
}

int Node::getName() const {
    return name;
}

void Node::addEdge(Node* node, int weight) {
    nodes.push_back(node);
    weights.push_back(weight);
}

int Node::getWeight(Node* node) const {
    for (int i = 0; i < (int)nodes.size(); i++) {
        if (nodes[i] == node)
            return weights[i];
    }
    return 0;
}

node_iterator Node::nb_begin() const {
    return nodes.begin();
}

node_iterator Node::nb_end() const {
    return nodes.end();
}

Graph::Graph() {
    for (int i = 1; i <= 9; i++)
        addNode(new Node(i));

    addEdge(1, 2, 10);
    addEdge(1, 4, 8);
    addEdge(1, 3, 6);
    addEdge(1, 5, 13);

    addEdge(2, 4, 5);
    addEdge(2, 7, 11);

    addEdge(3, 5, 3);

    addEdge(4, 3, 2);
    addEdge(4, 5, 5);
    addEdge(4, 6, 7);
    addEdge(4, 7, 12);

    addEdge(5, 6, 9);
    addEdge(5, 9, 12);

    addEdge(6, 8, 8);
    addEdge(6, 9, 10);

    addEdge(7, 6, 4);
    addEdge(7, 8, 6);
    addEdge(7, 9, 16);

    addEdge(8, 9, 15);
}

Graph::~Graph() {
    for (int i = 0; i < (int)nodes.size(); i++)
        delete nodes[i];
}

Node* Graph::getNode(int name) {
    for (int i = 0; i < (int)nodes.size(); i++) {
        if (nodes[i]->getName() == name)
            return nodes[i];
    }
    return 0;
}

void Graph::addNode(Node* node) {
    nodes.push_back(node);
}

void Graph::addEdge(int begin, int end, int weight) {
    Node* b = getNode(begin);
    Node* e = getNode(end);

    if (b != 0 && e != 0)
        b->addEdge(e, weight);
}

node_iterator Graph::begin() const {
    return nodes.begin();
}

node_iterator Graph::end() const {
    return nodes.end();
}

MarkedNode::MarkedNode(Node* anode, int amark, Node* aprev) {
    node = anode;
    mark = amark;
    prev = aprev;
}

MarkedNode PriorityQueue::pop() {
    int best = 0;

    for (int i = 1; i < (int)nodes.size(); i++) {
        if (nodes[i].mark < nodes[best].mark)
            best = i;
    }

    MarkedNode res = nodes[best];
    nodes.erase(nodes.begin() + best);
    return res;
}

void PriorityQueue::push(Node* node, int mark, Node* prev) {
    for (int i = 0; i < (int)nodes.size(); i++) {
        if (nodes[i].node == node) {
            if (mark < nodes[i].mark) {
                nodes[i].mark = mark;
                nodes[i].prev = prev;
            }
            return;
        }
    }

    nodes.push_back(MarkedNode(node, mark, prev));
}

bool PriorityQueue::empty() const {
    return nodes.empty();
}

Way::Way() {
    length = -1;
}

Dijkstra::Dijkstra(const Graph& agraph) : graph(agraph) {
}

Way Dijkstra::unroll(std::map<Node*, MarkedNode> visited, Node* begin, Node* curr) {
    Way way;
    way.length = visited[curr].mark;

    while (curr != begin) {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
    }

    way.nodes.push_back(begin);
    return way;
}

Way Dijkstra::shortestWay(Node* begin, Node* end) {
    PriorityQueue nodes;
    std::map<Node*, MarkedNode> visited;
    bool beginOk = false;
    bool endOk = false;

    for (node_iterator it = graph.begin(); it != graph.end(); it++) {
        if (*it == begin)
            beginOk = true;
        if (*it == end)
            endOk = true;
    }

    if (!beginOk || !endOk)
        return Way();

    nodes.push(begin, 0, 0);

    while (!nodes.empty()) {
        MarkedNode next = nodes.pop();

        if (visited.find(next.node) != visited.end())
            continue;

        visited[next.node] = next;

        if (next.node == end)
            return unroll(visited, begin, end);

        for (node_iterator it = next.node->nb_begin(); it != next.node->nb_end(); it++) {
            int weight = next.node->getWeight(*it) + next.mark;

            if (visited.find(*it) == visited.end())
                nodes.push(*it, weight, next.node);
        }
    }

    return Way();
}

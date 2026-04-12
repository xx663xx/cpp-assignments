#include "graph.h"

void Node::addNeighbour(Node* neighbour) {
    neighbours.insert(neighbour);
}

void Node::removeNeighbour(Node* neighbour) {
    neighbours.erase(neighbour);
}

void Graph::addNode(Node* node) {
    nodes.insert(node);
}

void Graph::removeNode(Node* node) {
    nodes.erase(node);
    for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->removeNeighbour(node);
    }
}

void Graph::addEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end) == nodes.end()) return;
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end) == nodes.end()) return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

Node* Graph::findNode(const std::string& name) const {
    for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        if ((*it)->getName() == name) return *it;
    }
    return 0;
}

Graph::Graph(const char* file_name) {
    std::ifstream fin(file_name);
    if (!fin) {
        std::cout << "Не удалось открыть файл: " << file_name << "\n";
        return;
    }

    std::string a, b;
    while (fin >> a >> b) {
        if (a == "Source" && b == "Target") continue;

        Node* n1 = findNode(a);
        Node* n2 = findNode(b);

        if (n1 == 0) {
            n1 = new Node(a);
            addNode(n1);
        }
        if (n2 == 0) {
            n2 = new Node(b);
            addNode(n2);
        }

        addEdge(n1, n2);
    }

    fin.close();
}

Graph::~Graph() {
    for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        delete *it;
    }
    nodes.clear();
}

void Graph::saveToFile(const char* file_name) const {
    std::ofstream fout(file_name);
    if (!fout) {
        std::cout << "Не удалось создать файл: " << file_name << "\n";
        return;
    }

    for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        Node* now = *it;
        for (node_iterator jt = now->nb_begin(); jt != now->nb_end(); jt++) {
            if (now->getName() < (*jt)->getName()) {
                fout << now->getName() << " " << (*jt)->getName() << "\n";
            }
        }
    }

    fout.close();
}

bool BFS::connected(Node* begin, Node* end) {
    std::queue<Node*> nodes;
    std::set<Node*> visited;
    nodes.push(begin);

    while (!nodes.empty()) {
        Node* next = nodes.front();
        nodes.pop();

        if (end == next) return true;
        visited.insert(next);

        for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++) {
            if (visited.find(*it) == visited.end()) {
                nodes.push(*it);
            }
        }
    }

    return false;
}

void BFS::findComponent(Node* begin, std::set<Node*>& used, std::set<Node*>& comp) {
    std::queue<Node*> q;
    q.push(begin);
    used.insert(begin);

    while (!q.empty()) {
        Node* now = q.front();
        q.pop();
        comp.insert(now);

        for (node_iterator it = now->nb_begin(); it != now->nb_end(); it++) {
            if (used.find(*it) == used.end()) {
                used.insert(*it);
                q.push(*it);
            }
        }
    }
}

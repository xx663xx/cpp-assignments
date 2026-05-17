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

    // Удаляем ссылки на вершину из всех списков соседей,
    // иначе в графе останутся висячие указатели.
    for (std::set<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->removeNeighbour(node);
    }
}

void Graph::addEdge(Node* begin, Node* end) {
    // Ребро можно построить только между вершинами, которые уже есть в графе.
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end) == nodes.end()) return;

    // Граф неориентированный, поэтому связь добавляется в обе стороны.
    begin->addNeighbour(end);
    end->addNeighbour(begin);
}

void Graph::removeEdge(Node* begin, Node* end) {
    // Если хотя бы одной вершины нет в графе, удалять нечего.
    if (nodes.find(begin) == nodes.end()) return;
    if (nodes.find(end) == nodes.end()) return;

    // Для неориентированного ребра нужно убрать обе половины связи.
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

Node* Graph::findNode(const std::string& name) const {
    // Вершины хранятся по указателям, поэтому поиск по имени выполняется вручную.
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
        // Файл может быть выгружен с заголовком таблицы Source Target.
        if (a == "Source" && b == "Target") continue;

        // Каждая строка задает одно ребро. Если вершины еще нет, создаем ее.
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
            // Ребро хранится у обеих вершин, но в файл его нужно записать один раз.
            // Сравнение имен выбирает единственное направление записи.
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

    // Обход в ширину постепенно раскрывает все вершины,
    // достижимые из begin. Если среди них есть end, вершины связаны.
    while (!nodes.empty()) {
        Node* next = nodes.front();
        nodes.pop();

        if (end == next) return true;
        visited.insert(next);

        for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++) {
            // В очередь попадают только вершины, которые еще не обрабатывались.
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

    // Компонента связности - это все вершины, до которых можно добраться
    // из стартовой вершины, двигаясь по ребрам графа.
    while (!q.empty()) {
        Node* now = q.front();
        q.pop();
        comp.insert(now);

        for (node_iterator it = now->nb_begin(); it != now->nb_end(); it++) {
            // used общий для всех компонент: он не дает начать новый обход
            // из вершины, которая уже вошла в найденную компоненту.
            if (used.find(*it) == used.end()) {
                used.insert(*it);
                q.push(*it);
            }
        }
    }
}

#include "graph.h"
#include <vector>

Graph makeGraphFromComponent(std::set<Node*>& comp) {
    Graph part;
    std::set<Node*>::iterator jt;

    // Сначала копируем в отдельный граф все вершины компоненты.
    // Ребра добавляются вторым проходом, когда все нужные вершины уже созданы.
    for (jt = comp.begin(); jt != comp.end(); jt++) {
        part.addNode(new Node((*jt)->getName()));
    }

    // Восстанавливаем только внутренние ребра компоненты,
    // сосед должен принадлежать тому же множеству comp.
    for (jt = comp.begin(); jt != comp.end(); jt++) {
        Node* old1 = *jt;
        Node* new1 = part.findNode(old1->getName());
        for (node_iterator kt = old1->nb_begin(); kt != old1->nb_end(); kt++) {
            if (comp.find(*kt) != comp.end()) {
                Node* new2 = part.findNode((*kt)->getName());
                part.addEdge(new1, new2);
            }
        }
    }

    return part;
}

std::vector<Graph> findNotCrossingGraphs(Graph& g) {
    std::vector<Graph> graphs;
    BFS bfs(g);
    std::set<Node*> used;

    // Проходим по всем вершинам. Если вершина еще не встречалась в обходах,
    // запускаем BFS и получаем новую компоненту связности.
    for (node_iterator it = g.begin(); it != g.end(); it++) {
        if (used.find(*it) == used.end()) {
            std::set<Node*> comp;
            bfs.findComponent(*it, used, comp);

            Graph part = makeGraphFromComponent(comp);
            graphs.push_back(part);
        }
    }

    return graphs;
}

int main() {
    // Загружаем исходный граф из файла со списком ребер.
    Graph g("testgraph.txt");
    if (g.size() == 0) {
        std::cout << "Не удалось прочитать testgraph.txt\n";
        return 0;
    }

    std::vector<Graph> graphs = findNotCrossingGraphs(g);

    // Каждая найденная компонента сохраняется в отдельный файл.
    for (int i = 0; i < (int)graphs.size(); i++) {
        std::string out_name = "component_" + std::to_string(i + 1) + ".txt";
        graphs[i].saveToFile(out_name.c_str());
    }

    std::cout << "Найдено " << graphs.size() << " компонент";
    return 0;
}

#include "graph.h"

int main() {
    Graph g("testgraph.txt");
    if (g.size() == 0) {
        std::cout << "Не удалось прочитать testgraph.txt\n";
        return 0;
    }

    BFS bfs(g);
    std::set<Node*> used;
    int num = 1;

    for (node_iterator it = g.begin(); it != g.end(); it++) {
        if (used.find(*it) == used.end()) {
            std::set<Node*> comp;
            bfs.findComponent(*it, used, comp);

            Graph part;
            std::set<Node*>::iterator jt;
            for (jt = comp.begin(); jt != comp.end(); jt++) {
                part.addNode(new Node((*jt)->getName()));
            }

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

            std::string out_name = "component_" + std::to_string(num) + ".txt";
            part.saveToFile(out_name.c_str());
            num++;
        }
    }

    std::cout << "Найдено " << num - 1 << " компонент";
    return 0;
}
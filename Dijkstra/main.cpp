#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph graph;
    Dijkstra dijkstra(graph);

    int begin, end;

    cout << "Введите начальную и конечную вершину, например: 1 9" << endl;
    cin >> begin >> end;

    Node* b = graph.getNode(begin);
    Node* e = graph.getNode(end);

    if (b == 0 || e == 0) {
        cout << "Такой вершины нет" << endl;
        return 0;
    }

    Way way = dijkstra.shortestWay(b, e);

    if (way.length == -1) {
        cout << "Путь не найден" << endl;
        return 0;
    }

    cout << "Длина пути: " << way.length << endl;
    cout << "Путь: ";

    for (int i = (int)way.nodes.size() - 1; i >= 0; i--) {
        cout << way.nodes[i]->getName();
        if (i != 0)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}

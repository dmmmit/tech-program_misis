#include <iostream>
#include <vector>
#include <limits.h>

struct Edge {
    int u, v, weight;
};

bool bellmanFord(int V, int E, std::vector<Edge>& edges, int source) {
    std::vector<int> distance(V, INT_MAX);  // Массив для хранения расстояний
    distance[source] = 0;  // Расстояние от источника до самого себя равно 0

    for (int i = 1; i < V; i++) {
        // Пройдем по всем рёбрам графа
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int weight = edges[j].weight;

            // Если можно улучшить расстояние до вершины v
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            std::cout << "Граф содержит отрицательный цикл!" << std::endl;
            return false;  // Если обнаружен отрицательный цикл
        }
    }

    std::cout << "Кратчайшие расстояния от вершины " << source << " до остальных вершин:" << std::endl;
    for (int i = 0; i < V; i++) {
        if (distance[i] == INT_MAX) {
            std::cout << "Вершина " << i << ": Недостижима" << std::endl;
        } else {
            std::cout << "Вершина " << i << ": " << distance[i] << std::endl;
        }
    }
    return true;
}

int main() {
    int V, E;
    std::cout << "Введите количество вершин и рёбер: ";
    std::cin >> V >> E;

    std::vector<Edge> edges(E);
    std::cout << "Введите рёбра в формате (u v вес): " << std::endl;
    for (int i = 0; i < E; i++) {
        std::cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    int source;
    std::cout << "Введите индекс источника: ";
    std::cin >> source;

    bellmanFord(V, E, edges, source);

    return 0;
}

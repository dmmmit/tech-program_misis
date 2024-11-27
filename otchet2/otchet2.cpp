#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Бесконечность

// Структура для хранения ребра графа
struct Edge {
    int to, weight;
};

// Алгоритм Дейкстры
vector<int> dijkstra(int start, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INF);              // Минимальные расстояния
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // Очередь с приоритетом

    dist[start] = 0;                       // Расстояние до начальной вершины
    pq.push({0, start});                   // {расстояние, вершина}

    while (!pq.empty()) {
        auto [current_dist, current] = pq.top();
        pq.pop();

        if (current_dist > dist[current])  // Если расстояние устарело, пропускаем
            continue;

        for (const auto& edge : graph[current]) {
            int next = edge.to;
            int weight = edge.weight;

            if (dist[current] + weight < dist[next]) {
                dist[next] = dist[current] + weight;
                pq.push({dist[next], next});
            }
        }
    }

    return dist; // Возвращаем вектор минимальных расстояний
}

int main() {
    int n, m;
    cout << "Введите количество вершин и ребер: ";
    cin >> n >> m;

    vector<vector<Edge>> graph(n); // Граф в виде списка смежности

    cout << "Введите ребра в формате: from to weight\n";
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Уберите эту строку для ориентированного графа
    }

    int start;
    cout << "Введите начальную вершину: ";
    cin >> start;

    vector<int> distances = dijkstra(start, graph);

    cout << "Минимальные расстояния от вершины " << start << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == INF) {
            cout << "До вершины " << i << " нет пути\n";
        } else {
            cout << "До вершины " << i << ": " << distances[i] << "\n";
        }
    }

    return 0;
}

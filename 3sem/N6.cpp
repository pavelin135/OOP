#include <iostream>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

#define V 6

/*-------------N6.1-------------*/
const int INF = numeric_limits<int>::max();

bool bfs(int rGraph[V][V], int s, int t, int parent[]) 
{
    vector<bool> visited(V, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}


/*-------------N6.2-------------*/

#define P 5 // Размер графа

bool isSafe(int v, bool graph[P][P], vector<int>& path, int pos) {
    if (!graph[path[pos - 1]][v]) {
        return false;
    }

    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true;
}

bool hamiltonianCycleUtil(bool graph[P][P], vector<int>& path, int pos) {
    if (pos == P) {
        // Проверка, существует ли ребро между последней вершиной и истоком
        return graph[path[pos - 1]][path[0]];
    }

    for (int v = 1; v < P; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(graph, path, pos + 1)) {
                return true;
            }

            path[pos] = -1;
        }
    }

    return false;
}

vector<int> hamiltonianCycle(bool graph[P][P]) {
    vector<int> path(P, -1);
    path[0] = 0;

    if (!hamiltonianCycleUtil(graph, path, 1)) {
        cout << "Гамильтонов цикл не существует." << endl;
        return vector<int>();
    }

    cout << "Гамильтонов цикл существует. Путь: ";
    for (int i : path) {
        cout << i << " ";
    }
    cout << path[0] << endl;

    return path;
}


/*-------------N6.3-------------*/


void colorGraph(bool graph[P][P]) {
    vector<int> colors(P, -1); // Инициализация массива цветов для каждой вершины

    // Первая вершина получает цвет 0
    colors[0] = 0;

    // Закрашиваем оставшиеся вершины
    for (int u = 1; u < P; u++) {
        // Проверяем цвета соседних вершин и закрашиваем текущую в противоположный цвет
        for (int v = 0; v < P; v++) {
            if (graph[u][v] && colors[v] != -1) {
                colors[u] = (colors[v] == 0) ? 1 : 0;
                break;
            }
        }
    }

    // Вывод цветов вершин
    cout << "Цвета вершин:\n";
    for (int i = 0; i < P; i++) {
        cout << "Вершина " << i << ": Цвет " << colors[i] << "\n";
    }
}


int main() {
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };

    int s = 0;
    int t = V - 1;

    cout << fordFulkerson(graph, s, t) << endl;

    // Пример графа в виде матрицы смежности
    bool graph1[P][P] = {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };

    hamiltonianCycle(graph1);


    // Пример графа в виде матрицы смежности
    bool graph2[P][P] = {
        {0, 1, 1, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };

    colorGraph(graph2);
    return 0;
}
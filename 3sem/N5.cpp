#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>

using namespace std;


// ----------- N5.1 ----------- //
void DFS(const vector<vector<int>>& G, int a, vector<bool>& V) 
{
    stack<int> s;
    s.push(a);
    V[a] = 1;

    while (!s.empty()) 
    {
        int current = s.top();
        s.pop();
        cout << current << " ";  

        for (int neighbor = 0; neighbor < G.size(); neighbor++)
        {
            if (G[current][neighbor] != 0 && !V[neighbor])
            {
                s.push(neighbor);
                V[neighbor] = 1;
            }
        }
    }
}



// ----------- N5.2 ----------- //
void Dijkstra(const vector<vector<int>>& G, int a, vector<int>& distances)
{
    int numVert = G.size();
    distances.resize(numVert, numeric_limits<int>::max());
    distances[a] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, a });

    while (!pq.empty())
    {
        int curDist = pq.top().first;
        int curVert = pq.top().second;
        pq.pop();

        if (curDist > distances[curVert])
            continue;

        for (int neighbor = 0; neighbor < numVert; neighbor++)
        {
            int edgeWeight = G[curVert][neighbor];
            if (edgeWeight > 0)
            {
                int newDist = distances[curVert] + edgeWeight;
                if (newDist < distances[neighbor])
                {
                    distances[neighbor] = newDist;
                    pq.push({ newDist, neighbor });
                }
            }
        }
    }
}


// ----------- N5.3 ----------- //

struct TreeNode 
{
    int val;
    vector<TreeNode*> children;

    TreeNode(int value)
    {
        val = value;
    }
};

// Функция для подсчета степени вершин в дереве
vector<int> countDegrees(TreeNode* root) 
{
    vector<int> degrees;
    if (!root)
        return degrees;


    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) 
    {
        TreeNode* current = q.front();
        q.pop();

        int degree = current->children.size();  // Степень текущей вершины
        degrees.push_back(degree);

        // Добавляем детей текущей вершины в очередь для обхода
        for (int i = 0; i < current->children.size(); i++)
        {
            TreeNode* child = current->children[i];
            q.push(child);
        }
    }

    return degrees;
}

// Функция для подсчета средней степени в дереве
double averageDegree(TreeNode* root) {
    vector<int> degrees = countDegrees(root);

    if (degrees.empty()) 
        return 0.0;

    double sum = 0.0;
    for (int i = 0; i < degrees.size(); i++)
        sum += degrees[i];

    return sum / degrees.size();
}


// ----------- N5.4 ----------- //

// Структура для представления ребра графа
struct Edge 
{
    int from;
    int to;
    int weight;

    Edge(int f, int t, int w)
    {
        from = f;
        to = t;
        weight = w;
    }
};

// Структура для сравнения ребер по весу
struct CompareEdges
 {
    bool operator()(const Edge& e1, const Edge& e2) {
        return e1.weight > e2.weight;
    }
};

// Функция для построения минимального остова по алгоритму Прима
vector<Edge> primMST(const vector<vector<int>>& G)
{
    int numVert = G.size();

    vector<bool> visited(numVert, 0);

    visited[0] = 1;

    priority_queue<Edge, vector<Edge>, CompareEdges> pq;

    for (int i = 0; i < numVert; i++) 
    {
        if (G[0][i] != 0) {
            pq.push(Edge(0, i, G[0][i]));
        }
    }

    vector<Edge> minSpanTree; 

    while (!pq.empty())
    {

        Edge currentEdge = pq.top();
        pq.pop();

        // Проверяем, чтобы избежать циклов
        if (!visited[currentEdge.to]) 
        {
           
            visited[currentEdge.to] = 1;

            minSpanTree.push_back(currentEdge);

            // Добавляем все ребра, связанные с текущей вершиной, в приоритетную очередь
            for (int i = 0; i < numVert; i++) 
            {
                if (G[currentEdge.to][i] != 0 && !visited[i])
                {
                    pq.push(Edge(currentEdge.to, i, G[currentEdge.to][i]));
                }
            }
        }
    }

    return minSpanTree;
}


//////////////

int main()
{
    vector<vector<int>> adjacencyMatrix = {
        { 0, 7, 7, 9, 0, 4, 7, 6, 4, 4, 1, 4 },
        { 7, 0, 7, 5, 5, 2, 1, 1, 8, 5, 9, 0 },
        { 7, 7, 0, 8, 9, 0, 9, 8, 9, 7, 4, 1 },
        { 9, 5, 8, 0, 7, 3, 9, 6, 5, 5, 5, 2 },
        { 0, 5, 9, 7, 0, 9, 9, 3, 5, 9, 0, 2 },
        { 4, 2, 0, 3, 9, 0, 3, 2, 3, 2, 9, 3 },
        { 7, 1, 9, 9, 9, 3, 0, 2, 7, 2, 4, 7 },
        { 6, 1, 8, 6, 3, 2, 2, 0, 3, 3, 6, 9 },
        { 4, 8, 9, 5, 5, 3, 7, 3, 0, 5, 6, 2 },
        { 4, 5, 7, 5, 9, 2, 2, 3, 5, 0, 6, 4 },
        { 1, 9, 4, 5, 0, 9, 4, 6, 6, 6, 0, 7 },
        { 4, 0, 1, 2, 2, 3, 7, 9, 2, 4, 7, 0 }
    };
    /*
    vector<vector<int>> adjacencyMatrix0 = {
        { 0, 7, 7, 9, 0, 4, 7, 6, 4, 4, 0, 4 },
        { 7, 0, 7, 5, 5, 2, 1, 1, 8, 5, 0, 0 },
        { 7, 7, 0, 8, 9, 0, 9, 8, 9, 7, 0, 1 },
        { 9, 5, 8, 0, 7, 3, 9, 6, 5, 5, 0, 2 },
        { 0, 5, 9, 7, 0, 9, 9, 3, 5, 9, 0, 2 },
        { 4, 2, 0, 3, 9, 0, 3, 2, 3, 2, 0, 3 },
        { 7, 1, 9, 9, 9, 3, 0, 2, 7, 2, 0, 7 },
        { 6, 1, 8, 6, 3, 2, 2, 0, 3, 3, 0, 9 },
        { 4, 8, 9, 5, 5, 3, 7, 3, 0, 5, 0, 2 },
        { 4, 5, 7, 5, 9, 2, 2, 3, 5, 0, 0, 4 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 4, 0, 1, 2, 2, 3, 7, 9, 2, 4, 0, 0 }
    };*/

    int numVertices = adjacencyMatrix.size();
    vector<bool> visited(numVertices, false);

    DFS(adjacencyMatrix, 0, visited);
    cout << endl;
    /*
    for (vector<bool>::iterator it = visited.begin(); it != visited.end(); it++)
        cout << *it << endl;*/

    int startVertex = 0;
    vector<int> distances;

    Dijkstra(adjacencyMatrix, startVertex, distances);

    for (int i = 0; i < distances.size(); ++i) {
        cout << "To vertex " << i << ": " << distances[i] << endl;
    }
    ////

    TreeNode* root = new TreeNode(1);
    root->children.push_back(new TreeNode(2));
    root->children.push_back(new TreeNode(3));
    root->children[0]->children.push_back(new TreeNode(4));
    root->children[1]->children.push_back(new TreeNode(5));
    root->children[1]->children.push_back(new TreeNode(6));

    double avg = averageDegree(root);


    cout << "Avg degree of the tree: " << avg<< endl;

    /////

    vector<Edge> minSpanningTree = primMST(adjacencyMatrix);

    return 0;
}
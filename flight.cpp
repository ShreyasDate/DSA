#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX = 50;
int adjacencyMatrix[MAX][MAX] = {0}; // Flight costs or distances
int dfsVisited[MAX] = {0};           // Track visited cities for DFS

// Perform DFS Traversal
void DFS(int start, int cityCount, string cities[]) {
    dfsVisited[start] = 1;
    cout << cities[start] << " ";

    for (int i = 0; i < cityCount; i++) {
        if (adjacencyMatrix[start][i] && !dfsVisited[i]) {
            DFS(i, cityCount, cities);
        }
    }
}

// Perform BFS Traversal
void BFS(int start, int cityCount, string cities[]) {
    vector<bool> visited(cityCount, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << cities[current] << " ";

        for (int i = 0; i < cityCount; i++) {
            if (adjacencyMatrix[current][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {
    int cityCount;
    cout << "Enter number of cities: ";
    cin >> cityCount;

    string cities[cityCount];
    for (int i = 0; i < cityCount; i++) {
        cout << "Enter city #" << i << " (Airport Code): ";
        cin >> cities[i];
    }

    // Input the adjacency matrix (distance or cost between cities)
    cout << "\nEnter flight distance (or cost) between cities:\n";
    for (int i = 0; i < cityCount; i++) {
        for (int j = i + 1; j < cityCount; j++) {
            cout << "Between " << cities[i] << " and " << cities[j] << ": ";
            cin >> adjacencyMatrix[i][j];
            adjacencyMatrix[j][i] = adjacencyMatrix[i][j]; // Undirected graph
        }
    }

    // Display adjacency matrix
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < cityCount; i++) {
        cout << cities[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < cityCount; i++) {
        cout << cities[i] << "\t";
        for (int j = 0; j < cityCount; j++) {
            cout << adjacencyMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    // DFS traversal
    int startCity;
    cout << "\nEnter starting city index for DFS (0 to " << cityCount - 1 << "): ";
    cin >> startCity;
    cout << "DFS Traversal: ";
    DFS(startCity, cityCount, cities);

    // BFS traversal
    cout << "\n\nEnter starting city index for BFS (0 to " << cityCount - 1 << "): ";
    cin >> startCity;
    cout << "BFS Traversal: ";
    BFS(startCity, cityCount, cities);

    return 0;
}

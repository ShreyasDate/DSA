#include <iostream>
using namespace std;

class MST {
    int cost[20][20];      // Adjacency matrix
    int visited[20];       // Visited array for Prim's
    int numBranches;       // Number of offices/vertices

public:
    void input() {
        int edges, u, v, w;

        cout << "Enter number of branches (offices): ";
        cin >> numBranches;

        // Initialize matrix with 999 (representing infinity/no connection)
        for (int i = 0; i < numBranches; i++) {
            visited[i] = 0;
            for (int j = 0; j < numBranches; j++) {
                cost[i][j] = 999;
            }
        }

        cout << "Enter number of connections: ";
        cin >> edges;

        for (int i = 0; i < edges; i++) {
            cout << "\nConnection #" << i + 1 << ":\n";
            cout << "Enter branches to connect (1-based index): ";
            cin >> u >> v;
            cout << "Enter cost for this connection: ";
            cin >> w;

            cost[u - 1][v - 1] = w;
            cost[v - 1][u - 1] = w;
        }
    }

    void display() {
        cout << "\nAdjacency Matrix:\n\n\t";
        for (int i = 0; i < numBranches; i++)
            cout << "B" << i + 1 << "\t";
        cout << endl;

        for (int i = 0; i < numBranches; i++) {
            cout << "B" << i + 1 << "\t";
            for (int j = 0; j < numBranches; j++) {
                if (cost[i][j] == 999)
                    cout << "-\t";
                else
                    cout << cost[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void primMST() {
        int totalCost = 0;
        for (int i = 0; i < numBranches; i++)
            visited[i] = 0;

        visited[0] = 1; // Start from branch 0

        cout << "\nMinimum cost connections:\n";

        for (int edge = 0; edge < numBranches - 1; edge++) {
            int min = 999, u = -1, v = -1;

            for (int i = 0; i < numBranches; i++) {
                if (visited[i]) {
                    for (int j = 0; j < numBranches; j++) {
                        if (!visited[j] && cost[i][j] < min) {
                            min = cost[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }

            if (u != -1 && v != -1) {
                visited[v] = 1;
                totalCost += cost[u][v];
                cout << "B" << u + 1 << " -> B" << v + 1 << " with cost: " << cost[u][v] << endl;
            }
        }

        cout << "\nTotal minimum cost: " << totalCost << endl;
    }
};

int main() {
    MST m;
    m.input();
    m.display();
    m.primMST();
    return 0;
}

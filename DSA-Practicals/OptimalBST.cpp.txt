#include<iostream>
using namespace std;

#define SIZE 10

class OBST {
    int p[SIZE];       // Successful search probabilities
    int q[SIZE];       // Unsuccessful search probabilities
    int a[SIZE];       // Sorted keys
    int w[SIZE][SIZE]; // Weight matrix
    int c[SIZE][SIZE]; // Cost matrix
    int r[SIZE][SIZE]; // Root matrix
    int n;             // Number of keys

public:
    void get_data() {
        cout << "\nOptimal Binary Search Tree\n";
        cout << "\nEnter number of keys: ";
        cin >> n;

        cout << "\nEnter the keys (in sorted order):\n";
        for (int i = 1; i <= n; i++) {
            cout << "a[" << i << "]: ";
            cin >> a[i];
        }

        cout << "\nEnter probabilities of successful search:\n";
        for (int i = 1; i <= n; i++) {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }

        cout << "\nEnter probabilities of unsuccessful search:\n";
        for (int i = 0; i <= n; i++) {
            cout << "q[" << i << "]: ";
            cin >> q[i];
        }
    }

    int Min_Value(int i, int j) {
        int min = 999999, k = 0;
        for (int m = r[i][j - 1]; m <= r[i + 1][j]; m++) {
            int temp = c[i][m - 1] + c[m][j];
            if (temp < min) {
                min = temp;
                k = m;
            }
        }
        return k;
    }

    void build_OBST() {
        for (int i = 0; i < n; i++) {
            w[i][i] = q[i];
            c[i][i] = 0;
            r[i][i] = 0;

            w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }

        w[n][n] = q[n];
        c[n][n] = 0;
        r[n][n] = 0;

        for (int m = 2; m <= n; m++) {
            for (int i = 0; i <= n - m; i++) {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j] + q[j];
                int k = Min_Value(i, j);
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
                r[i][j] = k;
            }
        }
    }

    void build_tree() {
        int queue[2 * SIZE];
        int front = -1, rear = -1;
        int i, j, k;

        cout << "\nOptimal Binary Search Tree Structure:\n";
        cout << "\nRoot of OBST: " << r[0][n];
        cout << "\nCost of OBST: " << c[0][n];

        cout << "\n\nNODE\tLEFT CHILD\tRIGHT CHILD";
        cout << "\n-----------------------------------------";

        queue[++rear] = 0;
        queue[++rear] = n;

        while (front != rear) {
            i = queue[++front];
            j = queue[++front];
            k = r[i][j];

            cout << "\n" << k;

            if (r[i][k - 1] != 0) {
                cout << "\t" << r[i][k - 1];
                queue[++rear] = i;
                queue[++rear] = k - 1;
            } else {
                cout << "\t-";
            }

            if (r[k][j] != 0) {
                cout << "\t\t" << r[k][j];
                queue[++rear] = k;
                queue[++rear] = j;
            } else {
                cout << "\t\t-";
            }

            cout << "\n-----------------------------------------";
        }
    }
};

int main() {
    OBST obj;
    obj.get_data();
    obj.build_OBST();
    obj.build_tree();
    return 0;
}

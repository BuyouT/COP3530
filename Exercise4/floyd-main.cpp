#include <iostream>

using namespace std;

// Set INF to a really high number
const int INF = 999;

int main() {

    int node;
    int edge;
    int query;

    cin >> node;

    cin >> edge;

    cin >> query;

    // Create matrix
    int b[node][node];

    // Set everything to INF
    for (int i = 0; i < node; ++i) {
        for (int j = 0; j < node; ++j) {
            b[i][j] = INF;
        }
    }

    // The cost to itself is 0
    for (int i = 0; i < node; ++i) {
        b[i][i] = 0; 
    }

    int x;
    int y;
    int z;
    // Scan the connection nodes and give it's weight
    cout << "Give edges" << endl;
    for (int i = 0; i < edge; ++i) {
        cin >> x >> y >> z;
        b[x-1][y-1] = z;
    }

    // matrix used for the path
    int a[node][node];

    for(int i = 0; i < node; i++){
        for(int j = 0; j < node; j++){
            if(i==j) {
                a[i][j] = i;
            }
            else if(b[i][j]!=0 && b[i][j] != INF ) {
                a[i][j] = i;
            }
            else {
                a[i][j] = -1;
            }
        }
    }

    // flowd-warshall algorithm
    for (int k = 0; k < node; k++) {

        for (int i = 0; i < node; i++) {

            for (int j = 0; j < node; j++) {

                if ((b[i][k] * b[k][j] != 0) && (i != j)) {

                    if ((b[i][k] + b[k][j] < b[i][j]) || (b[i][j] == 0)) {
                        b[i][j] = b[i][k] + b[k][j];
                        a[i][j] = k+1;
                    }
                }
            }
        }
    }

    // print the cost if thee is a path
    for (int i = 0; i < query; ++i) {
        cin >> x >> y;
        if (b[x-1][y-1] >= INF/2) {
            cout << "NO PATH" << endl;
        }
        else {
            cout << "cost = " << b[x-1][y-1] << endl;
            if (b[x-1][y-1] == 0) {
                cout << x << "-" << y;
            }
            // else {
            //     for (int j = 0; j < node; ++j) {
            //         cout << a[x-1][j] << "-";
            //     }
            // }
            cout << endl;
        }
    }

    // for (int i = 0; i < node; ++i) {
    //     for (int j = 0; j < node; ++j) {
    //         cout << a[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    return 0;
}
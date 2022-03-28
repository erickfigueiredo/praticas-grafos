#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define INF 987654321

vector<vector<int>> typedef graph;

void floydWarshall(graph& g) {
    const int SIZE = g.size();

    for (int k = 0; k < SIZE; k++)
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (g[i][k] != INF && g[k][j] != INF && g[i][j] > g[i][k] + g[k][j])
                    g[i][j] = g[i][k] + g[k][j];
}

int main() {
    int nSets = 1, nJunctions, nConn, s, d, nQueries, q;

    while (cin >> nJunctions) {

        vector<int> busynesses(nJunctions);

        for (int i = 0; i < nJunctions; i++) cin >> busynesses[i];

        cin >> nConn;

        graph g(nJunctions, vector<int>(nJunctions, INF));
        for (int i = 0; i < nJunctions; i++) g[i][i] = 0;

        while (nConn--) {
            cin >> s >> d;
            s--; d--;

            g[s][d] = pow(busynesses[d] - busynesses[s], 3);
        }

        cin >> nQueries;
        floydWarshall(g);

        cout << "Set #" << nSets++ << '\n';

        while (nQueries--) {
            cin >> q;
            q--;

            bool hasNegative = false;
            for (int i = 0; i < nJunctions; i++)
                if (g[0][i] != INF && g[i][q] != INF && g[i][i] < 0) {
                    hasNegative = true;
                    break;
                }

            (hasNegative || g[0][q] == INF || g[0][q] < 3) ? cout << "?\n" : cout << g[0][q] << '\n';
        }
    }
    return 0;
}
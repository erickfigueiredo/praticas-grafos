#include <iostream>
#include <vector>
#include <cmath>

#define INF 987654321

using namespace std;

vector <vector<int>> typedef graph;

int calcNTrips(int nPeople, int maxCapacity) {
    maxCapacity--; // Considera guia

    if (!maxCapacity) return INF;

    int nTrips = nPeople / maxCapacity;

    if (nPeople % maxCapacity) nTrips++;

    return nTrips;
}

void floydWarshall(graph& g, int nPeople) {
    const int SIZE = g.size();

    // Faz a conversão em Trips de cada duas cidades com conexão
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if(g[i][j] != INF)
                g[i][j] = calcNTrips(nPeople, g[i][j]);
    
    for (int k = 0; k < SIZE; k++)
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                g[i][j] = g[j][i] = min(g[i][j], max(g[i][k], g[k][j]));
}

int main() {
    int nCities, nEdges, cA, cB, limit, i = 0;

    while (true) {
        cin >> nCities >> nEdges;

        if (!nCities && !nEdges) break;

        graph g(nCities, vector<int>(nCities, INF));

        while (nEdges--) {
            cin >> cA >> cB >> limit;
            cA--; cB--;

            g[cA][cB] = g[cB][cA] = limit;
        }

        cin >> cA >> cB >> limit;
        cA--; cB--;
        
        floydWarshall(g, limit);

        printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", ++i, g[cA][cB]);
    }

    return 0;
}

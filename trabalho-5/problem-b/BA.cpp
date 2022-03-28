#include <iostream>
#include <vector>
#include <queue>
#include <list>

#define INF 987654321

using namespace std;

vector<list<pair<int, int>>> typedef graph;

int calcNTrips(int nPeople, int maxCapacity) {
    maxCapacity--; // Considera guia

    if (!maxCapacity) return INF;

    int nTrips = nPeople / maxCapacity;

    if (nPeople % maxCapacity) nTrips++;

    return nTrips;
}

int djikstra(const graph& g, int init, int goal) {
    const int L = g.size();
    int minNTrips = 1;

    vector<int>distance(L, INF);
    vector<int>visited(L, false);
    vector<pair<int, int>> parent(L, { -1,  0 });

    // O greater than após o container define que a prioridade será de forma crescente
    priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pQueue;

    distance[init] = 0;
    pQueue.push({ 0, init });

    while (!pQueue.empty()) {
        int v = pQueue.top().second;

        // Se já tem a menor distancia até o objetivo para de buscar
        if (v == goal) break;

        pQueue.pop();

        if (visited[v]) continue;
        visited[v] = true;

        for (const auto& c : g[v]) {
            int v1 = c.first, cost = c.second;

            if (distance[v1] > distance[v] + cost) {
                distance[v1] = distance[v] + cost;

                parent[v1] = { v, cost };

                pQueue.push({ distance[v1], v1});
            }
        }
    }

    for (int i = 0; i < L; i++)
        cout << i + 1 << " " << parent[i].first + 1 << " " << parent[i].second << '\n';

    return 0;
}

int main() {
    int nCities, nEdges, cA, cB, limit, i = 0;

    while (true) {
        cin >> nCities >> nEdges;

        if (!nCities && !nEdges) break;

        graph g(nCities);

        while (nEdges--) {
            cin >> cA >> cB >> limit;
            cA--; cB--;

            g[cA].push_back({ cB, limit });
            g[cB].push_back({ cA, limit });
        }

        // Partida - Destino - Passageiros
        cin >> cA >> cB >> limit;
        cA--; cB--;

        // Coverte o limite em número de Trips;
        for (auto& l : g)
            for (auto& c : l)
                c.second = calcNTrips(limit, c.second);

        printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", ++i, djikstra(g, cA, cB));
    }
    return 0;
}
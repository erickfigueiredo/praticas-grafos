#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<int> typedef graph;

bool isPossibleGraph(graph& g, int l) {

    // faz o processo para cada vertice do grafo
    for (int i = 0; i < l; i++) {
        // Ordena de forma decrescente
        sort(g.begin(), g.end(), greater<int>());

        // Se o maior grau for 0, acabou
        if (!g[0]) return true;

        // fixado o maior elemento removemos 1 grau dos outros vertices
        // até que um vertice seja negativo ou o maior vertice seja "consumido"
        for (int j = 1; j < l; j++) {
            g[j]--;
            g[0]--;

            if (g[j] < 0) return false;
            if (!g[0]) break;
        }

        // Se após remover 1 grau de todos os vértices, o vértice de maior
        // grau tiver valor maior que zero, significa que não há vertices suficientes.
        if (g[0]) return false;
    }

    return true;
}

int main() {
    int n = 0, dgree;

    while (true) {
        cin >> n;
        if (!n) break;

        graph g;

        for (int i = 0; i < n; i++) {
            cin >> dgree;
            g.push_back(dgree);
        }

        isPossibleGraph(g, n) ? cout << "Possible\n" : cout << "Not possible\n";
    }
    return 0;
}
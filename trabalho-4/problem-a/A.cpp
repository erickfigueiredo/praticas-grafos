#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Classe disponibilizada no material de aula
class UnionFind {
public:
    UnionFind(int tam) {
        representante.resize(tam);
        for (int i = 0;i < tam;i++)
            representante[i] = i;
    }
    //Retorna o representante do conjunto que contem
    //o elemento "elemento"
    int findSet(int elemento) {
        if (representante[elemento] == elemento)
            return elemento;
        //Compressao do caminho...
        representante[elemento] = findSet(representante[elemento]);
        return representante[elemento];
    }
    void mergeSets(int i, int j) {
        representante[findSet(i)] = findSet(j);
    }
    bool isSameSet(int i, int j) {
        return (findSet(i) == findSet(j));
    }

private:
    vector<int> representante;
};

struct Edge {
    int v, w;
    int cost;

    Edge(int v = -1, int w = -1, int cost = 0) : v(v), w(w), cost(cost) {}
};

bool operator <(const Edge& i, const Edge& j) {
    return i.cost < j.cost;
}

Edge calcCost(int v1, int v2, int id1, int id2) {
    int cost = 0;

    int ps1[4], ps2[4], aux1 = v1, aux2 = v2, dem = 0;

    // Separamos os digitos da senha
    for (int i = 3; i >= 0; i--) {
        dem = pow(10, i);

        ps1[i] = aux1 / dem;
        ps2[i] = aux2 / dem;

        aux1 = aux1 % dem;
        aux2 = aux2 % dem;

        // Analise de custo
        cost += min(abs(ps1[i] - ps2[i]), (min(ps1[i], ps2[i]) + (10 - max(ps1[i], ps2[i]))));
    }

    return Edge(id1, id2, cost);
}

int main() {
    int testCases, nPass;

    cin >> testCases;

    while (testCases--) {
        cin >> nPass;
        nPass++;

        // Lê todas as senhas
        vector<int> passwords(nPass);
        passwords[0] = 0;

        for (int i = 1; i < nPass; i++)
            cin >> passwords[i];

        vector<Edge> edges;

        // Parte do inicio
        for (int i = 0; i < nPass; i++)
            for (int j = i + 1; j < nPass; j++) {
                // chama a função de calc de custo e geração de aresta
                edges.push_back(calcCost(passwords[i], passwords[j], i, j));
            }

        // Ordena
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a < b;
            });

        UnionFind uf(nPass);

        int nConn = 0;
        int totalCost = 0;
        bool started = false;

        for (int i = 0; i < edges.size(); i++) {
            int compU = uf.findSet(edges[i].v);
            int compV = uf.findSet(edges[i].w);

            // 0000 não é uma senha, não pode ser um estado reaproveitado no JUMP
            if(!edges[i].v || !edges[i].w) {
                if(started) continue;
                else started = true;
            }

            // Se for diferente, pode ser unido
            if (compU != compV) {
                totalCost += edges[i].cost;
                uf.mergeSets(edges[i].v, edges[i].w);
                nConn++;

                if (nConn == nPass - 1) break; // otimização (árvore concluída)
            }
        }

        cout << totalCost << '\n';
    }

    return 0;
}

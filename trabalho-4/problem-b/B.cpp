#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

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
    float cost;

    Edge(int v = -1, int w = -1, float cost = 0) : v(v), w(w), cost(cost) {}
};

bool operator < (const Edge& i, const Edge& j) { return i.cost < j.cost; }

float euclidianDistance(const pair<int, int>& p, const pair<int, int>& q) {
    return sqrt(pow((p.first - q.first), 2) + pow((p.second - q.second), 2));
}

int main() {
    int testCases, nSat, nPosts, x, y;

    cin >> testCases;

    while (testCases--) {
        cin >> nSat >> nPosts;

        // Armazena os outPosts
        vector<pair<int, int>> points(nPosts);
        for (int i = 0; i < nPosts; i++) {
            cin >> x >> y;
            points[i] = make_pair(x, y);
        }

        vector <Edge> edges;
        for (int i = 0; i < nPosts; i++)
            for (int j = i + 1; j < nPosts; j++)
                edges.push_back(Edge(i, j, euclidianDistance(points[i], points[j])));

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a < b;
            });

        // Verifica se é possível
        UnionFind uf(nPosts);
        int nConn = 0;

        vector<float> d;

        for (int i = 0; i < edges.size(); i++) {
            int compU = uf.findSet(edges[i].v);
            int compV = uf.findSet(edges[i].w);

            // Se for diferente, pode ser unido
            if (compU != compV) {
                d.push_back(edges[i].cost);
                uf.mergeSets(edges[i].v, edges[i].w);
                nConn++;

                if (nConn == nPosts - 1) break; // otimização (árvore concluída)
            }
        }

        printf("%.2f\n", d[d.size() - nSat]);
    }

    return 0;
}

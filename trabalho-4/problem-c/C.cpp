#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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

    Edge(int v = -1, int w = -1,int cost = 0) : v(v), w(w), cost(cost) { }
};

bool operator <(const Edge &i,const Edge &j) {
	return i.cost < j.cost;
}

int main() {
    int nCities, nCons, c1, c2, n;
    string city;

    while (true) {
        cin >> nCities >> nCons;

        if (!nCities && !nCons) break;

        map<string, int> cityCode;

        for (int i = 0; i < nCities; i++) {
            cin >> city;

            cityCode.insert(make_pair(city, i));
        }

        vector<Edge> conn;
        Edge aux;

        while (nCons--) {
            cin >> city;
            c1 = cityCode.find(city)->second;

            cin >> city;
            c2 = cityCode.find(city)->second;

            cin >> n;

            aux.v = c1;
            aux.w = c2;
            aux.cost = n;

            conn.push_back(aux);
        }

        // Cidade de partida
        cin >> city;
        // usando cruscal pode ser ignorado pois não acumulamos vertices como em PRIM
        //c1 = cityCode.find(city)->second;

        sort(conn.begin(), conn.end(), [](const Edge &a, const Edge&b) {
            return a < b;
        });

        // Verifica se é possivel
        UnionFind uf(nCities);

        int totalCost = 0;
        int nConn = 0;

        for(int i = 0; i < conn.size(); i++) {
            int compU = uf.findSet(conn[i].v);
            int compV = uf.findSet(conn[i].w);
            
            // Se for diferente, pode ser unido
            if(compU != compV){
                totalCost += conn[i].cost;
                uf.mergeSets(conn[i].v, conn[i].w);
                nConn++;

                if(nConn == nCities-1) break; // otimização (árvore concluída)
            }
        }

        (nConn == nCities-1) ? cout << totalCost << '\n' : cout << "Impossible\n";
    }
    return 0;
}

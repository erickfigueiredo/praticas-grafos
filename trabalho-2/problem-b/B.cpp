#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <map>

using namespace std;

int euclidesMdc(int n1, int n2) {
    int res = n1 % n2;

    if (res == 1) return res;// Poupa +1 chamada desnecessária
    if (res == 0) return n2; // retorna o divisor

    return euclidesMdc(n2, res);
}

vector <list<pair<int, pair<int, int>>>> typedef adjList;

pair<int, int> dfsQueryFind(const adjList& l, const int init, const int goal, int q1, int q2, vector<bool>& v) {
    // Marca o inicial como visitado
    v[init] = true;
    int aux = q1, aux1 = q2, mdc;
    pair <int, int> r;

    list<pair<int, pair<int, int>>> ::const_iterator it = l[init].begin();

    while (it != l[init].end()) {
        if (!v[it->first]) {
            aux *= it->second.first;
            aux1 *= it->second.second;

            mdc = euclidesMdc(aux, aux1);

            aux /= mdc;
            aux1 /= mdc;

            if (it->first == goal) {
                return make_pair(aux, aux1);
            }

            r = dfsQueryFind(l, it->first, goal, aux, aux1, v);
            if (r.first != -1) return r;
        }

        aux = q1;
        aux1 = q2;

        it++;
    }

    return make_pair(-1, -1);
}

// Falta a DFS

int main() {
    int q1, q2, mdc, cursor = 0, i, j;
    string op, eq, p1, p2;
    pair<int, int> result;

    map<string, int> indexMapper;
    map<string, int>::iterator it;

    adjList exchange(60);

    while (true) {
        cin >> op;

        if (op == ".") break;

        // Assert
        if (op == "!") {
            cin >> q1 >> p1 >> eq >> q2 >> p2;

            it = indexMapper.find(p1);
            if (it == indexMapper.end()) {
                indexMapper.insert(make_pair(p1, cursor));
                i = cursor;
                cursor++;
            }
            else {
                i = it->second;
            }

            it = indexMapper.find(p2);
            if (it == indexMapper.end()) {
                indexMapper.insert(make_pair(p2, cursor));
                j = cursor;
                cursor++;
            }
            else {
                j = it->second;
            }

            // Pega o máximo divisor comum entre os dois valores
            mdc = euclidesMdc(q1, q2);

            q1 /= mdc;
            q2 /= mdc;

            // Depois que verificou se existe e criou, passa para a inserção dos valores na lista de adjacência
            exchange[i].push_back(make_pair(j, make_pair(q1, q2)));
            exchange[j].push_back(make_pair(i, make_pair(q2, q1)));
        }
        // Query
        else {
            cin >> p1 >> eq >> p2;

            it = indexMapper.find(p1);
            i = it->second; // Pego o índice do primeiro produto

            it = indexMapper.find(p2);
            j = it->second; // Pego o índice do segundo produto;

            q1 = 1; q2 = 1;

            vector <bool> visited(60, false);

            result = dfsQueryFind(exchange, i, j, q1, q2, visited);

            if (result.first != -1)
                cout << result.first << " " << p1 << " = " << result.second << " " << p2 << "\n";
            else
                cout << "? " << p1 << " = ? " << p2 << "\n";

        }
    }
    return 0;
}

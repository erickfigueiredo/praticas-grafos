#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

vector <vector<int>> typedef adjMatrix;

void dfs(adjMatrix& m, const int init, int& count, vector <bool>& v) {
    v[init] = true;

    for (int i = 0; i < m.size(); i++) {
        if (!v[i] && m[init][i]) {
            m[init][i] = 0;
            m[i][init] = 0;
            dfs(m, i, count, v);
        }
    }

    count++;
}

int main() {
    int n, aux, fixedIndex, start, criticalVertices = 0;
    string line;

    while (true) {
        cin >> n;

        if (!n) break;

        queue<int> v;
        for (int i = 0; i < n; i++) v.push(i);

        adjMatrix m(n, vector<int>(n));
        while (true) {
            getline(cin, line);
            if (line[0] == '0') break;

            istringstream iss(line);

            while (iss >> aux) {
                if (fixedIndex == -1) {
                    fixedIndex = aux;
                    continue;
                }

                else {
                    m[fixedIndex - 1][aux - 1]++;
                    m[aux - 1][fixedIndex - 1]++;
                }
                //cout << fixedIndex << " " << aux << endl;
            }
            fixedIndex = -1;
        }

        while (!v.empty()) {
            adjMatrix cpy = m;

            //Remove o vértice à frente na fila
            for (int i = 0; i < n; i++) {
                cpy[v.front()][i] = 0;
                cpy[i][v.front()] = 0;
            }

            /* for (const auto& r : cpy) {
                 for (const int c : r)
                     cout << c << ' ';

                 cout << '\n';
             } */

            int count = 0;

            vector <bool> visited(n, false);

            if(v.front() > 0) start = 0;
            else start = 1;

            dfs(cpy, start, count, visited);
            if (count < n - 1) criticalVertices++;
            /* cout << "Entrou" << endl;

               cout << "-----\n"; */

            v.pop();
        }
        cout << criticalVertices << '\n';

        criticalVertices = 0;

    }
    return 0;
}
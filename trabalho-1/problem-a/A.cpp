#include <iostream>
#include <vector>

using namespace std;

bool isIncident(const vector<vector<int>>& mtrx, const int row, const int col) {
    int conn = 0;
    int v[2];

    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            // Se achar um vertice na aresta contabiliza
            if (mtrx[j][i]) {
                conn++;
                // Pega os dois primeiros vertices e armazena
                if (conn < 3)
                    v[conn - 1] = j;

                else break; // Se achar mais de 2 sai
            }
        }

        if (conn != 2) return false; // Se tem um numero !=2, não pode

        // Senão varre toda a linha dos 2 vertices em busca de conexão dupla
        for (int k = i + 1; k < col; k++) {
            if (mtrx[v[0]][k] && mtrx[v[1]][k]) {
                return false; // Se achar, não é grafo simples
            }
        }

        conn = 0;
    }

    return true;
}

int main() {
    int nTests, n, m;
    cin >> nTests;

    for (int i = 0; i < nTests; i++) {
        cin >> n >> m;

        vector<vector<int>> incident(n, vector<int>(m));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> incident[i][j];

        isIncident(incident, n, m) ? cout << "Yes\n" : cout << "No\n";
    }
    return 0;
}

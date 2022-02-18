#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector <vector<char>> typedef graph;

// O pair interno guarda as coordenadas e o second mais externo o level
pair <pair<int, int>, int> typedef point;

int bfsFindScape(graph& m, point& j, const vector<point>& f) {
    point aux;
    queue <point> q;

    j.second = 1; // Inicializamos a posição de Joe como Nível 1
    q.push(j);

    // Adiciona o fogo à lista
    for (int i = 0; i < f.size(); i++)
        q.push(f[i]);

    while (!q.empty()) {
        j = q.front();
        q.pop();

        /* for (const auto& l : m) {
            for (const char c : l)
                cout << c << ' ';

            cout << endl;
        }
        cout << endl; */

        // Verificamos se o item na frente da fila é Joe
        if (m[j.first.first][j.first.second] == 'J') {
            if (j.first.first - 1 == -1 || j.first.first + 1 == m.size()
                || j.first.second - 1 == -1 || j.first.second + 1 == m[0].size())
                return j.second;

            // Como possuímos 4 possibilidades fixas (cima, baixo, esquerda, direita) marcamos e adicinamos na fila
            if (j.first.first - 1 >= 0 && m[j.first.first - 1][j.first.second] == '.') {
                m[j.first.first - 1][j.first.second] = 'J';

                aux = j;
                aux.first.first--;
                aux.second++;

                q.push(aux);
            }

            if (j.first.second - 1 >= 0 && m[j.first.first][j.first.second - 1] == '.') {
                m[j.first.first][j.first.second - 1] = 'J';

                aux = j;
                aux.first.second--;
                aux.second++;

                q.push(aux);
            }

            if (j.first.second + 1 < m[0].size() && m[j.first.first][j.first.second + 1] == '.') {
                m[j.first.first][j.first.second + 1] = 'J';

                aux = j;
                aux.first.second++;
                aux.second++;

                q.push(aux);
            }

            if (j.first.first + 1 < m.size() && m[j.first.first + 1][j.first.second] == '.') {
                m[j.first.first + 1][j.first.second] = 'J';

                aux = j;
                aux.first.first++;
                aux.second++;

                q.push(aux);
            }
        }
        else {
            if (j.first.first - 1 >= 0 && m[j.first.first - 1][j.first.second] != 'F' && m[j.first.first - 1][j.first.second] != '#') {
                m[j.first.first - 1][j.first.second] = 'F'; // Visita

                aux = j;
                aux.first.first--;

                q.push(aux); // Manda pra fila
            }

            if (j.first.second - 1 >= 0 && m[j.first.first][j.first.second - 1] != 'F' && m[j.first.first][j.first.second - 1] != '#') {
                m[j.first.first][j.first.second - 1] = 'F';

                aux = j;
                aux.first.second--;

                q.push(aux);
            }

            if (j.first.second + 1 < m[0].size() && m[j.first.first][j.first.second + 1] != 'F' && m[j.first.first][j.first.second + 1] != '#') {
                m[j.first.first][j.first.second + 1] = 'F';

                aux = j;
                aux.first.second++;

                q.push(aux);
            }

            if (j.first.first + 1 < m.size() && m[j.first.first + 1][j.first.second] != 'F' && m[j.first.first + 1][j.first.second] != '#') {
                m[j.first.first + 1][j.first.second] = 'F';

                aux = j;
                aux.first.first++;

                q.push(aux);
            }
        }
    }

    return -1;
}

int main() {
    int n, r, c, stp;
    point joe;

    cin >> n;

    while (n--) {
        cin >> r >> c;

        graph maze(r, vector<char>(c));

        vector<point> fs;

        // Leitura do Labirinto
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                cin >> maze[i][j];

                /// Captura a posição de Joe e do fogo
                if (maze[i][j] == 'J') {
                    joe.first.first = i;
                    joe.first.second = j;
                }

                if (maze[i][j] == 'F') {
                    fs.push_back(make_pair(make_pair(i, j), 0));
                }
            }

        stp = bfsFindScape(maze, joe, fs);

        if (stp != -1) cout << stp << "\n";
        else cout << "IMPOSSIBLE\n";
    }
    return 0;
}

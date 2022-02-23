#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(const vector<vector<char>>& g, pair<int, int> i) {
    int limitRow = g.size();
    int limitCol = g[0].size();

    vector<vector<bool>> v(limitRow, vector<bool>(limitCol, false));
    vector<vector<int>>path(limitRow, vector<int>(limitCol));
    queue<pair<int, int>> q;
    pair<int, int> aux;

    q.push(i);
    v[i.first][i.second] = true;
    path[i.first][i.second] = 0;

    while (!q.empty()) {
        i = q.front();
        q.pop();

        if (g[i.first][i.second] == 'G') 
            return path[i.first][i.second]; 

        if ((i.first + 1 < limitRow) && g[i.first + 1][i.second] != '#' && !v[i.first + 1][i.second]) {
            v[i.first + 1][i.second] = true;
            path[i.first + 1][i.second] = path[i.first][i.second] + 1;
            aux = i;

            aux.first++;

            q.push(aux);
        }
        if ((i.first - 1 >= 0) && g[i.first - 1][i.second] != '#' && !v[i.first - 1][i.second]) {
            v[i.first - 1][i.second] = true;
            path[i.first - 1][i.second] = path[i.first][i.second] + 1;
            aux = i;

            aux.first--;

            q.push(aux);
        }
        if ((i.second + 1 < limitCol) && g[i.first][i.second + 1] != '#' && !v[i.first][i.second + 1]) {
            v[i.first][i.second + 1] = true;
            path[i.first][i.second + 1] = path[i.first][i.second] + 1;
            aux = i;

            aux.second++;

            q.push(aux);
        }
        if ((i.second - 1 >= 0) && g[i.first][i.second - 1] != '#' && !v[i.first][i.second - 1]) {
            v[i.first][i.second - 1] = true;
            path[i.first][i.second - 1] = path[i.first][i.second] + 1;
            aux = i;

            aux.second--;

            q.push(aux);
        }
    }

    return -1;
}

int main() {
    int r, c, n, nRows, b;
    pair<int, int> init, goal;

    while (true) {
        cin >> r >> c;

        if (!r && !c) break;

        vector<vector<char>> grid(r, vector<char>(c, '.'));
        cin >> nRows;

        while (nRows--) {
            cin >> r >> n;

            while (n--) {
                cin >> b;
                grid[r][b] = '#';
            }
        }

        cin >> init.first >> init.second;
        cin >> goal.first >> goal.second;

        grid[init.first][init.second] = 'I';
        grid[goal.first][goal.second] = 'G';

        /* for(const auto &r : grid) {
            for(char col: r) cout << col << ' ';

            cout << endl;
        } */

        cout << bfs(grid, init) << '\n';
    }
    return 0;
}

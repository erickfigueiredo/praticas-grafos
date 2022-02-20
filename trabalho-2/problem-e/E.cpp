#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> typedef adjMatrix;
vector <int> typedef v;

void tarjan(const adjMatrix& m, int init, int& indexNode, v& disc, v& low, v& parent, vector <pair<int, int>>& b) {
    indexNode++;
    low[init] = disc[init] = indexNode;

    for (int i : m[init]) {
        if (!disc[i]) {
            parent[i] = init;

            tarjan(m, i, indexNode, disc, low, parent, b);

            // Na volta verificamos se é ponte
            if (low[i] > disc[init]) {
                if (init > i) b.push_back(make_pair(i, init));

                else b.push_back(make_pair(init, i));
            }

            low[init] = min(low[init], low[i]);
        }
        else if (i != parent[init]) {
            low[init] = min(low[init], disc[i]);
        }
    }
}

void findWeakLinks(const adjMatrix& m, vector <pair<int, int>>& b) {
    int l = m.size(), indexNode = 0;
    v parent(l, -1), low(l, 0), disc(l, 0);

    tarjan(m, 0, indexNode, disc, low, parent, b);
}

int main() {
    int n, m, v1, v2;

    while (true) {
        cin >> n >> m;

        if (!n && !m) break;
        adjMatrix adj(n);

        while (m--) {
            cin >> v1 >> v2;

            adj[v1].push_back(v2);
            adj[v2].push_back(v1);
        }

        vector <pair <int, int>> bridges;
        findWeakLinks(adj, bridges);


        cout << bridges.size();
        if (bridges.size() > 0) cout << ' ';

        sort(bridges.begin(), bridges.end(),
            [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
                if (a.first == b.first) return a.second < b.second;
                return a.first < b.first;
            });

        for (int i = 0; i < bridges.size(); i++) {
            cout << bridges[i].first << ' ' << bridges[i].second;
            if (i < bridges.size() - 1) cout << ' ';
        }

        cout << '\n';
    }

    return 0;
}

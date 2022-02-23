#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int bfsFindLongestRun(const vector<vector<int>>& area) {
    queue<pair<pair<int, int>, int>> qPath;
    pair<pair<int, int>, int> curr, aux;

    int rowLimit = area.size(), colLimit = area[0].size();

    int maximum = 1;

    for (int i = 0; i < area.size(); i++)
        for (int j = 0; j < area[0].size(); j++)
            qPath.push(make_pair(make_pair(i, j), 1));

    while (!qPath.empty()) {
        curr = qPath.front();
        qPath.pop();

        if (curr.first.first + 1 < rowLimit &&
            area[curr.first.first + 1][curr.first.second] < area[curr.first.first][curr.first.second]) {
            aux = curr;
            aux.first.first++;
            aux.second++;

            maximum = max(maximum, aux.second);

            qPath.push(aux);
        }

        if (curr.first.second + 1 < colLimit &&
            area[curr.first.first][curr.first.second + 1] < area[curr.first.first][curr.first.second]) {
            aux = curr;
            aux.first.second++;
            aux.second++;

            maximum = max(maximum, aux.second);

            qPath.push(aux);
        }

        if (curr.first.first - 1 >= 0 &&
            area[curr.first.first - 1][curr.first.second] < area[curr.first.first][curr.first.second]) {
            aux = curr;
            aux.first.first--;
            aux.second++;

            maximum = max(maximum, aux.second);

            qPath.push(aux);
        }

        if (curr.first.second - 1 >= 0 &&
            area[curr.first.first][curr.first.second - 1] < area[curr.first.first][curr.first.second]) {
            aux = curr;
            aux.first.second--;
            aux.second++;

            maximum = max(maximum, aux.second);

            qPath.push(aux);
        }
    }

    return maximum;
}

int main() {
    int testCases, r, c;
    string name;

    cin >> testCases;

    while (testCases--) {
        cin >> name >> r >> c;

        vector<vector<int>> area(r, vector<int>(c));
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) cin >> area[i][j];


        cout << name << ": " << bfsFindLongestRun(area) << '\n';
    }
    return 0;
}

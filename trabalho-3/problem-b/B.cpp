#include <iostream>
#include <vector>
#include <list>

using namespace std;

int dfsCalcPossibilities(const vector<list<int>>& l, vector<int>& b, int init) {
    list<int> ::const_iterator it = l[init].begin();

    if(l[init].empty()) return 1;

    while(it != l[init].end()) {
        if(!b[*it])
            b[*it] = dfsCalcPossibilities(l, b, *it);

        b[init] += b[*it];
        it++;
    }

    return b[init];
}

int main() {
    int nTests, choices, c;
    char chr[2];
    bool isFirst = true;

    while (true) {
        cin >> nTests;
        if (cin.eof()) break;

        vector<list<int>> lifetime(nTests);

        for (int i = 0; i < nTests; i++) {
            cin >> choices;

            while (choices--) {
                cin >> c;

                lifetime[i].push_back(c);
            }
        }

        vector <int> nBranches(nTests);

        if (isFirst) isFirst = false;
        else  cout << '\n';

        cout << dfsCalcPossibilities(lifetime, nBranches, 0) << '\n';
    }

    return 0;
}

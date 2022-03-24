#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string>
#include <sstream>

using namespace std;

vector<list<int>> typedef graph;

void dfsCat(const graph& g, int init, vector<pair<bool, bool>>& v) {
    if (v[init].first) return;
    v[init].first = true;

    for (int room : g[init]) dfsCat(g, room, v);
}

void dfsMouse(const graph& g, int init, vector<pair<bool, bool>>& v, const int home, bool& isSafe, int count = 0) {
    if (init == home && count > 1) isSafe = true;

    if (v[init].second) return;
    v[init].second = true;

    if (v[init].first) return;

    for (int room : g[init])
        dfsMouse(g, room, v, home, isSafe, count + 1);
}

bool checkMeet(const vector<pair<bool, bool>>& v) {
    for (const auto& p : v) if (p.first && p.second) return true;

    return false;
}

int main() {
    int testCases, nRooms, catRoom, mouseRoom, r1, r2;
    string aux = "";

    cin >> testCases;

    do {
        cout << aux;

        cin >> nRooms >> catRoom >> mouseRoom;

        catRoom--; mouseRoom--;

        graph gCat(nRooms);
        graph gMouse(nRooms);

        while (true) {
            cin >> r1 >> r2;
            if (r1 == -1) break;
            r1--; r2--;

            gCat[r1].push_back(r2);
        }
        bool test = false;
        cin.ignore();
        while (getline(cin, aux)) {
            if (aux == "") break;

            stringstream ss(aux);

            ss >> r1 >> r2;

            if (r1 == -1) break;
            r1--; r2--;

            gMouse[r1].push_back(r2);
        }


        vector<pair<bool, bool>> visitedRooms(nRooms, make_pair(false, false));

        dfsCat(gCat, catRoom, visitedRooms);

        bool isSafe = false;
        dfsMouse(gMouse, mouseRoom, visitedRooms, mouseRoom, isSafe);


        (checkMeet(visitedRooms)) ? cout << "Y " : cout << "N ";

        (isSafe) ? cout << "Y\n" : cout << "N\n";

        aux = "\n";
    } while (--testCases);

    return 0;
}

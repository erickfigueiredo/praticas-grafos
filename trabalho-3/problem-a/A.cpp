#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

void bfsGossipEmployee(const vector<list<int>>& emp, int gossiper) {
    queue <int> qEmployee;
    vector<bool> knowNews(emp.size(), false);
    vector<int> dayKnow(emp.size());

    list<int>::const_iterator it;

    dayKnow[gossiper] = 0;
    knowNews[gossiper] = true;
    qEmployee.push(gossiper);


    pair<int, int> curr(1, 0), max(1, 0);

    while (!qEmployee.empty()) {
        gossiper = qEmployee.front();
        qEmployee.pop();

        it = emp[gossiper].begin();
        while (it != emp[gossiper].end()) {
            if (!knowNews[*it]) {
                knowNews[*it] = true;
                dayKnow[*it] = dayKnow[gossiper] + 1;

                if (dayKnow[*it] == curr.first) curr.second++;
                else {
                    if (curr.second > max.second)
                        max = curr;

                    curr = make_pair(dayKnow[*it], 1);
                }

                qEmployee.push(*it);
            }
            it++;
        }
    }

    // verifica o último contabilizado
    if(curr.second > max.second) max = curr;

    if(!max.second) cout << "0\n";
    else cout << max.second << " " << max.first << '\n';
}

int main() {
    int nEmployees, nFriends, nTests, e;

    cin >> nEmployees;

    vector<list<int>> vEmployees(nEmployees);

    for (int i = 0; i < nEmployees; i++) {
        cin >> nFriends;

        while (nFriends--) {
            cin >> e;

            vEmployees[i].push_back(e);
        }
    }

    cin >> nTests;

    while (nTests--) {
        cin >> e;

        bfsGossipEmployee(vEmployees, e);
    }

    return 0;
}

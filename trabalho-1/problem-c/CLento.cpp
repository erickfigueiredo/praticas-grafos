#include <iostream>
#include <vector>

using namespace std;

void swapColor(pair<int, int>& p) {
    int aux = p.first;
    p.first = p.second;
    p.second = aux;
}

void swapBead(pair<int, int>& p, pair<int, int>& q) {
    auto aux = p;
    p = q;
    q = aux;
}

// passar o bead, itens concatenados, itens restantes
bool isPossibleToConcat(vector <pair<int, int>>& nl, int currIndex = 1) {

    if (currIndex == nl.size() - 1 && nl[0].first == nl[nl.size() - 1].second)
        return true;

    for (int i = currIndex; i < nl.size(); i++) {

        if (nl[currIndex - 1].second == nl[i].first || nl[currIndex - 1].second == nl[i].second) {
            if (nl[currIndex - 1].second == nl[i].second) swapColor(nl[i]); 

            if (currIndex != i) swapBead(nl[currIndex], nl[i]);

            if (isPossibleToConcat(nl, currIndex + 1)) return true;

            if (currIndex != i) swapBead(nl[currIndex], nl[i]);
        }
    }

    return false;
}
// Matriz de Adjacencia -> Encontrar varios ciclos -> Tentar juntar e ir girando os ciclos
int main() {
    int nTests, nBeads;

    cin >> nTests;

    for (int i = 0; i < nTests;i++) {
        cin >> nBeads;
        vector<pair<int, int>> bLace(nBeads);

        for (int j = 0; j < nBeads; j++) {
            cin >> bLace[j].first;
            cin >> bLace[j].second;
        }

        printf("Case #%d\n", i+1);
        if (isPossibleToConcat(bLace))
            for (const auto& p : bLace)
                printf("%d %d\n", p.first, p.second);

        else cout << "some beads may be lost\n";
        if(i != nTests-1) cout << '\n';
    }
    return 0;
}

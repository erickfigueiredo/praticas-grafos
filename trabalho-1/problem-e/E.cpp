#include <iostream>
#include <algorithm>

#include <map>
#include <vector>

using namespace std;

vector <vector<char>> typedef graph;

void showRanking(map<char, int>& mp, int i) {
    // Ordena em ordem decrescente

    // Copiamos para um vector que pode aplicar sort
    vector<pair<char, int>> elems(mp.begin(), mp.end());
    stable_sort(elems.begin(), elems.end(), [](pair<char, int>a, pair<char,int>b){
        return a.second > b.second;
    });

    // Imprime o ranking
    cout << "World #" << i + 1 << endl;
    for (auto& el : elems)
        cout << el.first << ": " << el.second << endl;
}

// Usamos a ideia do algoritmo de flood fill
void fillMap(graph& g, const char selectedChar, int currX, int currY, const int limitX, const int limitY) {
    // Preenche a posição atual como "Visitada"
    g[currX][currY] = '0';

    // Checa se as posições acima, abaixo, a esquerda e a direita
    // Verifica se perdencem ao mesmo país e se esta nos limites do mapa
    if (currX - 1 >= 0 && g[currX - 1][currY] == selectedChar)
        fillMap(g, selectedChar, currX - 1, currY, limitX, limitY);

    if (currX + 1 < limitX && g[currX + 1][currY] == selectedChar)
        fillMap(g, selectedChar, currX + 1, currY, limitX, limitY);

    if (currY - 1 >= 0 && g[currX][currY - 1] == selectedChar)
        fillMap(g, selectedChar, currX, currY - 1, limitX, limitY);

    if (currY + 1 < limitY && g[currX][currY + 1] == selectedChar)
        fillMap(g, selectedChar, currX, currY + 1, limitX, limitY);
}

int main() {
    int testCases, n, m;

    cin >> testCases;

    for (int i = 0; i < testCases; i++) {
        cin >> n >> m;
        graph g(n, vector<char>(m));
        map <char, int> countingLanguages;

        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
                cin >> g[j][k];

        // Inicia a varredura no mapa
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
                if (g[j][k] != '0') { // Se a posição não estiver sido visitada
                    countingLanguages[g[j][k]]++; // Preenche que mais um país fala a lingua
                    fillMap(g, g[j][k], j, k, n, m); // Limpa todo o país
                }

        showRanking(countingLanguages, i);
    }
    return 0;
}
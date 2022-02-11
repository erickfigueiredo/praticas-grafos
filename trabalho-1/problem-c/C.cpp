#include <iostream>
#include <vector>

using namespace std;

void findNextBead(vector <vector<int>>& m, int& sumE, const int row, vector <int>& necklace) {
    // Varre todas as colunas da linha, buscando outra cor que se ligue a cor da linha
    for (int i = 0; i < 50; i++) {
        // Se encontrar um vértice na coluna com algum grau
        if (m[row][i]) {
            // Adiciona ao colar e remove a aresta
            m[row][i]--;
            m[i][row]--;

            sumE--; // Remove uma aresta do total

            // Verifica se é possivel continuar da coluna (que passa a ser linha)
            findNextBead(m, sumE, i, necklace);
        }
    }
    // Na volta da recursão guarda o row (Não se pode salvar antes da recursão pois um caminho pode não levar a lugar algum)
    necklace.push_back(row + 1);

    // Não há mais miçangas que se conectem ao colar
}

// Estamos em busca de um grafo euleriano que seja composto por um único ciclo
// É determinado que serão no máximo 50 cores, logo criamos as matrizes com valor estático para facilitar o mapeamento
int main() {
    int testCases, nBeads, c1, c2, sumEdge = 0;
    bool isEulerian = true;

    cin >> testCases;

    for (int i = 0; i < testCases; i++) {
        // Cria Matriz de Adjacencia que armazena a conexão de cores de uma mesma miçanga
        // Cores -> Vértices, presença em uma mesma miçanga -> arestas
        vector <vector <int>> adjMatrix(50, vector<int>(50));

        // O objetivo é verificar um ciclo Euleriano
        // Armazena o grau, caso algum vértice possua grau ímpar, o grafo não é euleriano
        vector<int> colourDegree(50);

        cin >> nBeads;

        for (int j = 0; j < nBeads; j++) {
            cin >> c1 >> c2;

            c1--;
            c2--;

            // Incrementamos o grau das cores
            colourDegree[c1]++;
            colourDegree[c2]++;

            // Marca a aresta na matriz de adjacência
            adjMatrix[c1][c2]++;
            adjMatrix[c2][c1]++;

            // Incrementamos o número de vertices presentes no grafo
            sumEdge++;
        }

        printf("Case #%d\n", i + 1);

        // Verifica se algum vértice possui grau ímpar, caso true, não é euleriano
        for (int i = 0; i < 50; i++)
            if (colourDegree[i] % 2 != 0) {
                isEulerian = false;
                break;
            }

        if (!isEulerian) {
            cout << "some beads may be lost\n\n";

            isEulerian = true;
            sumEdge = 0;

            continue;
        }

        vector <int> orderedNecklace;

        // Passamos um dos dois ultimos verices informados pois precisamos ter de onde começar a traçar o caminho
        findNextBead(adjMatrix, sumEdge, c2, orderedNecklace);

        // Caso todos os vértices tenham sido consumidos, é um grafo conexo e uma forma de montar o colar foi obtida
        if (!sumEdge) {

            // Como em cada miçanga temos duas cores, imprimimos a posição seguinte do vetor que indica que as duas cores estão na
            // mesma miçanga
            for (int k = 0; k < nBeads; k++)
                cout << orderedNecklace[k] << ' ' << orderedNecklace[k + 1] << endl;
        }
        else { cout << "Some beads may be lost\n"; }
        cout << "\n";

        isEulerian = true;
        sumEdge = 0;
    }
    return 0;
}

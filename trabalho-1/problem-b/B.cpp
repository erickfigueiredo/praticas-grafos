# include <iostream>
# include <set>
# include <string>

using namespace std;

int main() {
    int testCases, nEdges = 0, nVertices, nComponents, nAcorns, nTrees;
    string row;

    cin >> testCases;

    while (testCases--) {
        set <char> verticesWithEdges; // Armazena os vertices com conexão
        while (true) {
            cin >> row;

            if (row[0] == '*') break;

            nEdges++; // Incrementamos o número de arestas

            // Como a linha está formatada, sabemos onde encontrar os vertices
            verticesWithEdges.insert(row[1]);
            verticesWithEdges.insert(row[3]);

        } // Termina de ler as arestas

        // Lê o conjunto de Vertices
        cin >> row;

        nVertices = row.length() - ((row.length() - 1) / 2); // Descontamos as virgulas;

        /**
         * Sabemos que em uma árvore |E| = |V|-1, como já comprovado na lista de exercicios,
         * logo, como as entradas ou serão árvores ou pontos com grau 0, se subtrairmos o total
         * de arestas do total de vertices, teremos o numero de componentes desconexos (pois de cada
         * árvore restará um, e de cada acorn, ele mesmo).
         *
        */

        nComponents = nVertices - nEdges;

        // Acorns não tem conxão, logo não estão presentes em arestas
        nAcorns = nVertices - verticesWithEdges.size(); 
        
        // Sabendo o numero de acorns, basta descontar do número de componentes
        nTrees = nComponents - nAcorns;

        printf("There are %d tree(s) and %d acorn(s).\n", nTrees, nAcorns);

        nEdges = 0;
    }
    return 0;
}
#include <iostream>

using namespace std;

int main() {
    int n, t, index = 0;

    cin >> n >> t;

    t--; // Descontamos 1 de t pois iniciamos de 0
    n--; // Descontamos 1 pois consideramos as arestas entre vertices
    
    int cell[n];

    // Leitura do número de celulas
    for (int i = 0; i < n; i++)
        cin >> cell[i];

    // Vai andando pelas celulas enquanto o indíce for menor que o desejado
    while (index < t)
        index += cell[index];
    

    // Se alcançou o índice é possível ir para a célula usando o sistema de transporte
    cout << (index == t ? "YES" : "NO") << "\n";

    return 0;
}

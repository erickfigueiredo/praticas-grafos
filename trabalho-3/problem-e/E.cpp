#include <iostream>
#include <string>

using namespace std;

const int HORSE_MOVES[][2] = {
    {-1,2}, {1,2}, {-1, -2}, {1, -2},
    {-2, 1}, {2, 1}, {-2, -1}, {2, -1}
};

bool checkFinal(char b[][5]) {
    const char FINAL_POSITION[5][5] = {
        {'1', '1', '1', '1', '1'},
        {'0', '1', '1', '1', '1'},
        {'0', '0', ' ', '1', '1'},
        {'0', '0', '0', '0', '1'},
        {'0', '0', '0', '0', '0'},
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (b[i][j] != FINAL_POSITION[i][j])
                return false;

    return true;
}

int dfsMinMoves(char b[][5], pair< int, int>& c, pair<int, int>& l, int moves = 0) {
    // Retorna se o movimento passar de 10 ou se chegou no objetivo 
    if (moves > 10 || checkFinal(b)) return moves;

    int minMoves = 11;
    pair<int, int> aux;

    // Movimenta entre as oito posições
    for (int i = 0; i < 8; i++) {
        // Pega a nova posição do cavalo
        aux.first = c.first + HORSE_MOVES[i][0];
        aux.second = c.second + HORSE_MOVES[i][1];

        if (aux.first >= 0 && aux.first < 5
            && aux.second >= 0 && aux.second < 5
            && aux != l) {
            // Movimenta o cavalo, se não der certo volta
            swap(b[c.first][c.second], b[aux.first][aux.second]);
            
            // O movimento mínimo vai receber o minimo entre o atual e o retornado
            minMoves = min(dfsMinMoves(b, aux, c, moves + 1), minMoves);
            swap(b[c.first][c.second], b[aux.first][aux.second]);
        }
    }

    return minMoves;
}

int main() {
    int nTests, min;
    string in;

    cin >> nTests; cin.ignore();

    while (nTests--) {
        char board[5][5];
        pair<int, int> curr, last;

        for (int i = 0; i < 5; i++) {
            getline(cin, in);

            for (int j = 0; j < 5; j++) {
                board[i][j] = in[j];

                if (in[j] == ' ')
                    curr = make_pair(i, j);
            }
        }


        min = dfsMinMoves(board, curr, last);

        if (min < 11) printf("Solvable in %d move(s).\n", min);
        else cout << "Unsolvable in less than 11 move(s).\n";
    }

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

// Matriz da posição final desejada
const char FINAL_POSITION[5][5] = {
        {'1', '1', '1', '1', '1'},
        {'0', '1', '1', '1', '1'},
        {'0', '0', '2', '1', '1'},
        {'0', '0', '0', '0', '1'},
        {'0', '0', '0', '0', '0'},
};

// Possibilidades de movimento dos cavalos em volta do setor
const char X[8] = { -1, 1, -2, 2, -1, 1, -2, 2 };
const char Y[8] = { 2, 2, 1, 1, -2, -2, -1, -1 };

bool checkFinalPosition(char b[][5]) {
    if (b[2][2] != ' ') return false;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (b[i][j] != FINAL_POSITION[i][j])
                return false;

    return true;
}




int main() {
    int nTests, min;
    string in;

    cin >> nTests; cin.ignore();

    while (nTests--) {
       

        for (int i = 0; i < 5; i++) {
            cin >> in;

            for (int j = 0; j < 5; j++) {
                cg.board[i][j] = in[j];

                if (in[j] == ' ') {
                    
                }
            }
        }


       

        if (min < 11) printf("Solvable in %d move(s).\n", min);
        else printf("Unsolvable in less than 11 move(s).\n");
    }

    return 0;
}
#include <iostream>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS
int q[NN], qf, qb, previous[NN];

int fordFulkerson(int n, int s, int t) {
    // init the flow network
    memset(fnet, 0, sizeof(fnet));

    int flow = 0;

    while (true) {
        // find an augmenting path
        memset(previous, -1, sizeof(previous));
        qf = qb = 0;
        previous[q[qb++] = s] = -2;
        while (qb > qf && previous[t] == -1)
            for (int u = q[qf++], v = 0; v < n; v++)
                if (previous[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v])
                    previous[q[qb++] = v] = u;

        // see if we're done
        if (previous[t] == -1) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for (int v = t, u = previous[v]; u >= 0; v = u, u = previous[v])
            bot = min(cap[u][v] - fnet[u][v] + fnet[v][u], bot);

        // update the flow network
        for (int v = t, u = previous[v]; u >= 0; v = u, u = previous[v])
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

int main() {
    int nTests, shirts, volunteers, shirtEach, s1, s2;
    string aux;

    // Não começa de 0 pois temos que inserir uma origem
    const map<string, int> sizes = { {"XXL", 1}, {"XL", 2}, {"L", 3}, {"M", 4},
    {"S", 5}, {"XS", 6} };

    cin >> nTests;

    while (nTests--) {
        cin >> shirts >> volunteers;

        shirtEach = shirts / 6;

        // Preenche primeiro indo da origem e distribuindo as qtd de cada tamanho
        for (int i = 1; i < 7; i++) cap[0][i] = shirtEach;

        // Sabemos que s = 0 é a origem
        // Sabemos que os proximos 6 vertices são tamanhos
        // Volunteers vertices serão voluntarios
        // Sabemos que o vertice destino será dado por 7 (pois é 0 - 6) + volunteers 
        const int END = volunteers + 7;

        for (int i = 7; i < END; i++) {
            cin >> aux;
            s1 = sizes.find(aux)->second;
            cin >> aux;
            s2 = sizes.find(aux)->second;

            cap[s1][i] = cap[i][s1] = 1;
            cap[s2][i] = cap[i][s2] = 1;

            cap[i][END] = cap[END][i] = 1;
        }

        // |V| = SOURCE + SIZES + END + VOLUNTEERS
        const int N_VERTICES = 8 + volunteers;

        (volunteers == fordFulkerson(N_VERTICES, 0, END)) ?
            cout << "YES\n" : cout << "NO\n";

        for(int i = 0; i < N_VERTICES; i++)
            for(int j = 0; j < N_VERTICES; j++)
                cap[i][j] = 0;
    }

    return 0;
}

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS
int q[NN], qf, qb, previous[NN];

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true ){
        // find an augmenting path
        memset( previous, -1, sizeof( previous ) );
        qf = qb = 0;
        previous[q[qb++] = s] = -2;
        while( qb > qf && previous[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( previous[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    previous[q[qb++] = v] = u;

        // see if we're done
        if( previous[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = previous[v]; u >= 0; v = u, u = previous[v] )
            bot = min(cap[u][v] - fnet[u][v] + fnet[v][u], bot);

        // update the flow network
        for( int v = t, u = previous[v]; u >= 0; v = u, u = previous[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

int main() {
    int nNodes, s, t, c, n1, n2, bw, i = 1;

    while (cin >> nNodes) {
        if (!nNodes) break;

        cin >> s >> t >> c;
        s--; t--;

        while (c--) {
            cin >> n1 >> n2 >> bw;
            n1--; n2--;
            cap[n1][n2] += bw;
            cap[n2][n1] += bw;
        }
        
        // Calculate
        printf("Network %d\nThe bandwidth is %d.\n\n", i++, fordFulkerson(nNodes, s, t));

        for(int i = 0; i < NN; i++)
            for(int j = 0; j < NN; j++)
                cap[i][j] = 0;
    }

    return 0;
}

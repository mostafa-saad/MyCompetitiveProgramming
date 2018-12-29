/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Dawid Dabrowski                               *
 *   Zlozonosc czasowa:    O(n^3 + k)                                    *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Algorytm Floyda-Warshalla                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define min(a, b) ((a) < (b) ? (a) : (b))

const int MX = 5000;
const short int INF = 10005;

int n, m, ntc;

short int d[MX][MX][2];
bool isolated[MX];

int main() {
    scanf("%d%d%d", &n, &m, &ntc);
    for (int i = 0; i < n; ++i) for(int j = 0; j < n; ++j)
            d[i][j][0] = d[i][j][1] = INF;
    for (int i = 0; i < n; ++i)
        d[i][i][0] = 0;
    for (int i = 0; i < n; ++i)
        isolated[i] = true;
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u;
        --v;
        d[u][v][1] = d[v][u][1] = 1;
        isolated[u] = isolated[v] = false;
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                d[i][j][0] = min(d[i][j][0],
                                 min(d[i][k][0] + d[k][j][0],
                                     d[i][k][1] + d[k][j][1]));
                d[i][j][1] = min(d[i][j][1],
                                 min(d[i][k][1] + d[k][j][0],
                                     d[i][k][0] + d[k][j][1]));
            }
    for (int tc = 0; tc < ntc; ++tc) {
        int u, v, dist;
        scanf("%d%d%d", &u, &v, &dist);
        --u;
        --v;
        if (u == v && isolated[u] && dist > 0) printf("NIE\n");
        else if (d[u][v][dist&1] == INF) printf("NIE\n");
        else printf(d[u][v][dist&1] <= dist ? "TAK\n" : "NIE\n");
    }
    return 0;
}

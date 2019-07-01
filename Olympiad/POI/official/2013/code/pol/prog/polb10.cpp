/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Losuje skierowanie krawedzi i sprawdza wynik  *
 *                         algorytmem Warshalla.                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

typedef long long int LL;

const int MAXN = 1000;
const int INF = 99999999;
const int MAX_OP = 50000000;

int minRes = INF, maxRes = 0, res;
pair<int,int> edges[MAXN];
bool d[MAXN][MAXN];

int main() {
    int N;

    scanf("%d", &N);

    for (int i = 0; i < N-1; i++) {
        int u, v;

        scanf("%d%d", &u, &v);
        u--;
        v--;

        edges[i] = make_pair(u, v);
    }

    srand(N*3+N/3);

    int numChecks = MAX_OP / (N*N*N);

    while (numChecks--) {
        for (int i = 0; i < N; i++) {
            fill(d[i], d[i]+N, false);
            d[i][i] = true;
        }

        for (int i = 0; i < N-1; i++) {
            if (rand()%2 == 0)
                d[edges[i].first][edges[i].second] = true;
            else
                d[edges[i].second][edges[i].first] = true;
        }

        res = 0;

        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    d[i][j] = d[i][j] || (d[i][k] && d[k][j]);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (d[i][j])
                    res++;

        res -= N;

        minRes = min(minRes, res);
        maxRes = max(maxRes, res);
    }

    printf("%d %d\n", minRes, maxRes);

    return 0;
}

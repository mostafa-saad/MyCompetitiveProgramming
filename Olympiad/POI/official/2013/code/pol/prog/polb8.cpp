/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Losuje skierowanie krawedzi i sprawdza wynik. *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

const int MAXN = 1000;
const int INF = 99999999;
const int MAX_OP = 150000000;

int minRes = INF, maxRes = 0, res;
pair<int,int> edges[MAXN];
vector<int> adj[MAXN];
bool visited[MAXN];

void Dfs(int u) {
    visited[u] = true;
    res++;

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]])
            Dfs(adj[u][i]);
}

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

    int numChecks = MAX_OP / (5*N + 3*N*N);

    while (numChecks--) {
        for (int i = 0; i < N; i++)
            adj[i].clear();

        for (int i = 0; i < N-1; i++) {
            if (rand()%2 == 0)
                adj[edges[i].first].push_back(edges[i].second);
            else
                adj[edges[i].second].push_back(edges[i].first);
        }

        res = 0;

        for (int i = 0; i < N; i++) {
            fill(visited, visited+N, false);
            Dfs(i);
        }

        res -= N;

        minRes = min(minRes, res);
        maxRes = max(maxRes, res);
    }

    printf("%d %d\n", minRes, maxRes);

    return 0;
}

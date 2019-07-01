/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Luk triumfalny                                *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;

vector<int> adj[MAXN];
bool visited[MAXN];

int Check(int u, int k) {
    int numChildren = 0, sumTree = 0;

    visited[u] = true;

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]]) {
            numChildren++;
            sumTree += Check(adj[u][i], k);
        }

    return max(0, numChildren+sumTree-k);
}

int main() {
    int ret, N, fromSearch = 0, toSearch;

    ret = scanf("%d", &N);
    if (ret < 0)
        return 0;
    for (int i = 0; i < N-1; i++) {
        int u, v;

        ret = scanf("%d%d", &u, &v);
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    toSearch = N;

    while (fromSearch < toSearch) {
        int centSearch = (fromSearch+toSearch)/2;

        fill(visited, visited+N, false);

        if (Check(0, centSearch) == 0)
            toSearch = centSearch;
        else
            fromSearch = centSearch+1;
    }

    printf("%d\n", fromSearch);

    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Luk triumfalny                                *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
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
    int N, ret;

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

    for (int i = 0; i <= N; i++) {
        fill(visited, visited+N, false);

        if (Check(0, i) == 0) {
            printf("%d\n", i);
            return 0;
        }
    }

    return 0;
}

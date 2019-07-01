/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Luk triumfalny                                *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zwraca liczbe synow wierzcholka, ktory        *
 *                         posiada ich najwiecej.                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;

vector<int> adj[MAXN];
bool visited[MAXN];

int Dfs(int u) {
    int result = 0, curRes = 0;

    visited[u] = true;

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]]) {
            result = max(result, Dfs(adj[u][i]));
            curRes++;
        }

    return max(result, curRes);
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

    printf("%d\n", Dfs(0));

    return 0;
}

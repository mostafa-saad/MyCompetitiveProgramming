/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Luk triumfalny                                *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Oblicza odleglosci od korzenia, nastepnie     *
 *                         probuje pokrywac kolejne poziomy.             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;

int numD[MAXN], maxD = 0;
vector<int> adj[MAXN];
bool visited[MAXN];

void Dfs(int u, int curD) {
    visited[u] = true;
    numD[curD]++;
    maxD = max(maxD, curD);

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]])
            Dfs(adj[u][i], curD+1);
}

int main() {
    int ret, N, result = 0;

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

    Dfs(0, 0);

    N--;
    while (N > 0) {
        int canUse = 0;

        result++;

        for (int i = 1; i <= maxD; i++) {
            canUse++;
            while ((canUse > 0) && (numD[i] > 0)) {
                canUse--;
                numD[i]--;
                N--;
            }
        }
    }

    printf("%d\n", result);

    return 0;
}

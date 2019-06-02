/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    pesymistycznie O(qn), srednio O(q+n)          *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Bliskie wzorcowemu. Brakuje struktury         *
 *                         pozwalajacej szybko aktualizowac liczby       *
 *                         zajetych wierzcholkow w danym poziomie.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;
const int MAXQ = 1000001;

int n, m, t[MAXN], q[MAXQ], d[MAXN], s[MAXN], result[MAXN], maxD = 0;
vector<int> adj[MAXN];

void Dfs(int u) {
    for (unsigned i = 0; i < adj[u].size(); i++) {
        d[adj[u][i]] = d[u]+1;
        Dfs(adj[u][i]);
    }
    s[d[u]]++;
    maxD = max(maxD, d[u]);
}

int main() {
    int ret;

    ret = scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++)
        ret = scanf("%d", &q[i]);

    for (int i = 1; i < n; i++) {
        ret = scanf("%d", &t[i]);
        t[i]--;

        adj[t[i]].push_back(i);
    }

    if (ret < 0)
        return 1;

    Dfs(0);

    for (int i = n; i >= 1; i--) {
        for (int j = 0; s[j] > 0; j++) {
            if (s[j] > i) {
                s[j+1] += s[j]-i;
                s[j] = i;
            }
            maxD = max(maxD, j);
        }
        result[i] = maxD+1;
    }

    for (int i = 0; i < m; i++) {
        if (i > 0) printf(" ");
        printf("%d", result[min(q[i],n)]);
    }
    printf("\n");

    return 0;
}

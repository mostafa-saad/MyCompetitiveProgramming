/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(qn)                                         *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Heurystyka. Zlicza wierzcholki na kazdym      *
 *                         poziomie drzewa i dzieli przez liczbe         *
 *                         procesorow.                                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define F first
#define S second

const int MAXN = 1000001;
const int MAXQ = 1000001;

int n, m, t[MAXN], q[MAXQ], d[MAXN], s[MAXN];
vector<int> adj[MAXN];

void Dfs(int u) {
    for (unsigned i = 0; i < adj[u].size(); i++) {
        d[adj[u][i]] = d[u]+1;
        Dfs(adj[u][i]);
    }
    s[d[u]]++;
}

int Compute(int x) {
    int result = 0;

    for (int i = 0; s[i] > 0; i++)
        result += (s[i]+x-1)/x;

    return result;
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

    for (int i = 0; i < m; i++) {
        if (i > 0) printf(" ");
        printf("%d", Compute(q[i]));
    }
    printf("\n");

    return 0;
}

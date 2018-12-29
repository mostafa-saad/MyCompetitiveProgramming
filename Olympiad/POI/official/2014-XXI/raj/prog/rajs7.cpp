/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m + 2^n * n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Znajdowanie wszystkich sciezek                *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 500 * 1000;

vector<int> G[N + 1];
int ret[N + 1];
bool st[N + 1];

void dfs(int v, int l, int n) {
    st[v] = true;
    for(int i=1; i<= n; i++) {
        if(!st[i]) ret[i] = max(ret[i], l);
    }

    for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++)
        dfs(*it, l+1, n);

    st[v] = false;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
    }

    for(int i=1; i<=n; i++) dfs(i, 0, n);

    int *me = min_element(ret+1, ret+1+n);
    printf("%ld %d\n", long(me - ret), *me);

}

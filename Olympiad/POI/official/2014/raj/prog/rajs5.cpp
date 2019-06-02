/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(n(n+m))                                     *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego wierzcholka lezacego na jakiejs   *
 *                         najdluzszej sciezce brutalnie liczymy wynik.  *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

const int N = 500 * 1000;

vector<int> G[N + 1];
int topo[N + 1];
int indeg[N + 1];
int res[N + 1];

int maxin[N + 1];
int maxout[N + 1];

void toposort(int n) {
    queue<int> kol;
    for(int i=1; i<=n; i++) if(indeg[i] == 0) kol.push(i);

    int nr = 0;
    while(!kol.empty()) {
        int v = kol.front();
        kol.pop();

        topo[++nr] = v;

        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            indeg[*it] --;
            if(indeg[*it] == 0) kol.push(*it);
        }
    }
}

int dp[N + 1];

int calc(int k, int n) {
    fill(dp + 1, dp + n + 1, 0);
    for(int i=1; i<=n; i++) {
        int v = topo[i];
        if(v == k) dp[v] = numeric_limits<int>::min();

        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            dp[*it] = max(dp[*it], dp[v] + 1);
        }
    }
    return *max_element(dp+1, dp+1+n);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        indeg[b] ++;
    }

    toposort(n);

    for(int i=1; i<=n; i++) {
        int v = topo[i];
        for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++) {
            maxin[*it] = max(maxin[*it], maxin[v] + 1);
        }
    }

    for(int i=n; i>=1; i--) {
        int v = topo[i];
        for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++) {
            maxout[v] = max(maxout[v], maxout[*it] + 1);
        }
    }

    int max_len = *max_element(maxin+1, maxin+n+1);

    for(int i=1; i<=n; i++) {
        if(maxin[i] + maxout[i] == max_len)
            res[i] = calc(i, n);
        else
            res[i] = numeric_limits<int>::max();
    }

    int* me = min_element(res+1, res+1+n);
    printf("%ld %d\n", long(me - res), *me);
}

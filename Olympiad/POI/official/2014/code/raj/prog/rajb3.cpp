/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Blokuje srodek pewnej najdluzszej sciezki.    *
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
int topor[N + 1];
int indeg[N + 1];

int maxin[N + 1];
int maxout[N + 1];
int result[N + 1];

void toposort(int n) {
    queue<int> kol;
    for(int i=1; i<=n; i++)
        if(indeg[i] == 0) kol.push(i);

    int nr = 0;
    while(!kol.empty()) {
        int v = kol.front();
        kol.pop();

        topo[++nr] = v;
        topor[v] = nr;
        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            indeg[*it] --;
            if(indeg[*it] == 0) kol.push(*it);
        }
    }
}


int dp[N + 1];
bool vis[N + 1];

void dfs(int v, int k) {
    if(vis[v]) return;
    vis[v] = true;
    if(v == k) return;

    for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
        if(!vis[*it])
            dfs(*it, k);
        dp[v] = max(dp[v], dp[*it] + 1);
    }

}

int calc(int k, int n) {
    fill(dp+1, dp+1+n, 0);
    fill(vis+1, vis+1+n, 0);
    dp[k] = numeric_limits<int>::min();
    for(int i=1; i<=n; i++) if(!vis[i]) dfs(i, k);
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

    int maxlen = *max_element(maxout + 1, maxout + 1 + n);

    fill(result + 1, result + 1 + n, numeric_limits<int>::max());

    for(int i=1; i<=n; i++) {
        if(maxin[i] + maxout[i] == maxlen && abs(maxin[i] - maxout[i]) <= 1) {
            result[i] = calc(i, n);
            break;
        }
    }

    int* me = min_element(result + 1, result + n+1);

    printf("%ld %d\n", long(me - result), *me);
}

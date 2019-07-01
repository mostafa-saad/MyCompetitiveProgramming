/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Rekurencyjne sortowanie topologiczne          *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 500 * 1000;
const int PN = 1 << 19;
const int M = 1000 * 1000;

vector<int> G[N + 1];
int topo[N + 1];
int topor[N + 1];
int indeg[N + 1];

int maxin[N + 1];
int maxout[N + 1];
int result[N + 1];

bool vis[N + 1];
int order;

void dfs(int v) {
    vis[v] = true;

    for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
        if(!vis[*it])
            dfs(*it);
    }
    topor[v] = order;
    topo[order--] = v;
}

void toposort(int n) {
    order = n;
    for(int i=1; i<=n; i++) if(!vis[i]) dfs(i);
}

int tree[2 * PN];

void _tree_set(int ss, int ee, int s, int e, int x, int v) {
    if(ee < s || e < ss) return ;
    if(s <= ss && ee <= e) {
        tree[x] = max(tree[x], v);
        return;
    }
    int m = (ss + ee)/2;
    _tree_set(ss, m, s, e, 2*x, v);
    _tree_set(m+1, ee, s, e, 2*x+1, v);
}

void tree_set(int s, int e, int v) {
    _tree_set(1, PN, s, e, 1, v);
}

int tree_get(int x) {
    int ret = 0;
    x += PN - 1;
    while(x) {
        ret = max(ret, tree[x]);
        x/=2;
    }
    return ret;
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

    for(int v=1; v<=n; v++) {
        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            int u = *it;
            if(topor[u] > topor[v] + 1)
                tree_set(topor[v] + 1, topor[u] - 1, maxin[v] + 1 + maxout[u]);
        }
    }

    for(int i=1; i<=n; i++) {
        result[i] = tree_get(topor[i]);
    }

    int pmax = 0;
    for(int i=2; i<=n; i++) {
        result[topo[i]] = max(pmax = max(pmax, maxin[topo[i-1]]), result[topo[i]]);
    }

    int smax = 0;
    for(int i=n-1; i>=1; i--) {
        result[topo[i]] = max(smax = max(smax, maxout[topo[i+1]]), result[topo[i]]);
    }

    int* me = min_element(result + 1, result + n+1);

    printf("%ld %d\n", long(me - result), *me);
}

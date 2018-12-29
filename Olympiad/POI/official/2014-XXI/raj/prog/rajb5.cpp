/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Brak sortowania topologicznego.               *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int N = 500 * 1000;
const int PN = 1 << 19;

vector<int> G[N + 1];

int maxin[N + 1];
int maxout[N + 1];
int result[N + 1];

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
    }

    for(int v=1; v<=n; v++) {
        for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++) {
            maxin[*it] = max(maxin[*it], maxin[v] + 1);
        }
    }

    for(int v=n; v>=1; v--) {
        for(vector<int>::iterator it = G[v].begin(); it!=G[v].end(); it++) {
            maxout[v] = max(maxout[v], maxout[*it] + 1);
        }
    }

    for(int v=1; v<=n; v++) {
        for(vector<int>::iterator it = G[v].begin(); it != G[v].end(); it++) {
            int u = *it;
            if(u > v + 1)
                tree_set(v + 1, u - 1, maxin[v] + 1 + maxout[u]);
        }
    }

    for(int i=1; i<=n; i++) {
        result[i] = tree_get(i);
    }

    int pmax = 0;
    for(int i=2; i<=n; i++) {
        result[i] = max(pmax = max(pmax, maxin[i-1]), result[i]);
    }

    int smax = 0;
    for(int i=n-1; i>=1; i--) {
        result[i] = max(smax = max(smax, maxout[i+1]), result[i]);
    }

    int* me = min_element(result + 1, result + n+1);

    printf("%ld %d\n", long(me - result), *me);
}

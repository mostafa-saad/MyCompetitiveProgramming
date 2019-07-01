/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 500005;
const int MAXTREE = 524288;

int dpLeft[MAXN], dpRight[MAXN], tree[2*MAXTREE], revSorted[MAXN];
vector<int> adj[MAXN], adjRev[MAXN], sorted;
bool visited[MAXN];

void Dfs(int u) {
    visited[u] = true;

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]])
            Dfs(adj[u][i]);

    sorted.push_back(u);
}

void TreeSet(int from, int to, int val) {
    from += MAXTREE;
    to += MAXTREE;

    if (from > to)
        return;

    tree[from] = max(tree[from], val);
    tree[to] = max(tree[to], val);

    while (from/2 != to/2) {
        if (from%2 == 0)
            tree[from+1] = max(tree[from+1], val);
        if (to%2 == 1)
            tree[to-1] = max(tree[to-1], val);
        from /= 2;
        to /= 2;
    }
}

int TreeGet(int pos) {
    int result = 0;

    pos += MAXTREE;

    while (pos > 0) {
        result = max(result, tree[pos]);
        pos /= 2;
    }

    return result;
}

int main() {
    int n, m, u, v, result = MAXN, resultID = -1, curMax;

    scanf("%d%d", &n, &m);
    while (m--) {
        scanf("%d%d", &u, &v);
        u--;
        v--;

        adj[u].push_back(v);
        adjRev[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
        if (!visited[i])
            Dfs(i);

    reverse(sorted.begin(), sorted.end());

    for (int i = 0; i < (int)sorted.size(); i++)
        revSorted[sorted[i]] = i;

    curMax = 0;
    for (int i = 0; i < (int)sorted.size(); i++) {
        u = sorted[i];
        TreeSet(i, i, max(curMax, dpLeft[u]-1));
        curMax = max(curMax, dpLeft[u]);
        for (int j = 0; j < (int)adj[u].size(); j++)
            dpLeft[adj[u][j]] = max(dpLeft[adj[u][j]], dpLeft[u]+1);
    }

    curMax = 0;
    for (int i = (int)sorted.size()-1; i >= 0; i--) {
        u = sorted[i];
        TreeSet(i, i, max(curMax, dpRight[u]-1));
        curMax = max(curMax, dpRight[u]);
        for (int j = 0; j < (int)adjRev[u].size(); j++)
            dpRight[adjRev[u][j]] = max(dpRight[adjRev[u][j]], dpRight[u]+1);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < (int)adj[i].size(); j++) {
            int u = revSorted[i], v = revSorted[adj[i][j]];
            TreeSet(u+1, v-1, dpLeft[i]+dpRight[adj[i][j]]+1);
        }

    for (int i = 0; i < n; i++) {
        int thisResult = TreeGet(i);

        if (thisResult < result) {
            result = thisResult;
            resultID = sorted[i];
        }
    }

    printf("%d %d\n", resultID+1, result);

    return 0;
}

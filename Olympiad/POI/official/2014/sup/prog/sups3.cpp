/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(qn log n)                                   *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 1000001;
const int MAXQ = 1000001;

bool completed[MAXN];
int n, parent[MAXN], d[MAXN], q[MAXQ], t[MAXN], childCompleted[MAXN];
vector<int> adj[MAXN];

struct TCmp {
    bool operator() (int a, int b) {
        if (d[a] != d[b])
            return (d[a] > d[b]);
        return (a < b);
    }
};

set<int, TCmp> Q, newQ, leaves;

void Dfs(int u) {
    bool isLeaf = true;

    for (unsigned i = 0; i < adj[u].size(); i++) {
        parent[adj[u][i]] = u;
        d[adj[u][i]] = d[u]+1;
        Dfs(adj[u][i]);
        isLeaf = false;
    }
    if (isLeaf)
        leaves.insert(u);
}

int ComputeQuery(int maxTurn) {
    int result = 0, numCompleted = 0;

    fill(completed, completed+n, false);
    fill(childCompleted, childCompleted+n, 0);

    newQ = leaves;

    while (numCompleted < n) {
        for (set<int,TCmp>::iterator it = newQ.begin(); it != newQ.end(); it++)
            Q.insert(*it);
        newQ.clear();

        for (int i = 0; i < maxTurn; i++) {
            int u;

            if (Q.empty())
                break;

            u = *(Q.begin());

            Q.erase(Q.begin());

            completed[u] = true;
            if (u != 0) {
                childCompleted[parent[u]]++;

                if ((unsigned)childCompleted[parent[u]] == adj[parent[u]].size())
                    newQ.insert(parent[u]);
            }
            numCompleted++;
        }

        result++;
    }

    return result;
}

int main() {
    int ret, m;

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

    parent[0] = -1;

    for (int i = 0; i < m; i++) {
        if (i > 0) printf(" ");
        printf("%d", ComputeQuery(q[i]));
    }
    printf("\n");

    return 0;
}

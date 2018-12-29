/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(q*n^2*k)                                    *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000001;
const int MAXQ = 1000001;

bool completed[MAXN];
int n, t[MAXN], q[MAXQ], d[MAXN], parent[MAXN], maxLvl = 0, origMaxLvl = 0, completedLvl[MAXN], childCompleted[MAXN];
vector<int> adj[MAXN], lvl[MAXN], turnCompleted;

void Dfs(int u) {
    for (unsigned i = 0; i < adj[u].size(); i++) {
        parent[adj[u][i]] = u;
        d[adj[u][i]] = d[u]+1;
        Dfs(adj[u][i]);
    }
    lvl[d[u]].push_back(u);
    maxLvl = max(maxLvl, d[u]);
}

int FindNext() {
    for (int i = maxLvl; i >= 0; i--) {
        if ((unsigned)completedLvl[i] == lvl[i].size())
            continue;

        for (unsigned j = 0; j < lvl[i].size(); j++) {
            int u = lvl[i][j];

            if ((!completed[u]) && ((unsigned)childCompleted[u] == adj[u].size()))
                return u;
        }
    }

    return -1;
}

void MarkPath(int u, bool value) {
    if (u < 0)
        return;

    while (u != -1) {
        completed[u] = value;
        u = parent[u];
    }
}

int ComputeQuery(int maxTurn) {
    int result = 0, numCompleted = 0;

    maxLvl = origMaxLvl;

    fill(completed, completed+n, false);
    fill(completedLvl, completedLvl+maxLvl+1, 0);
    fill(childCompleted, childCompleted+n, 0);

    while (numCompleted < n) {
        for (int i = 0; i < maxTurn; i++) {
            int u = FindNext();

            if (u != -1) {
                MarkPath(u, true);
                if (u != 0)
                    childCompleted[parent[u]]++;
                turnCompleted.push_back(u);
                numCompleted++;
                completedLvl[d[u]]++;

                while ((unsigned)completedLvl[maxLvl] == lvl[maxLvl].size())
                    maxLvl--;
            }
            else
                break;
        }

        for (unsigned i = 0; i < turnCompleted.size(); i++)
            MarkPath(parent[turnCompleted[i]], false);

        turnCompleted.clear();

        result++;
    }

    return result;
}

int main() {
    int m, ret;

    ret = scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++)
        ret = scanf("%d", &q[i]);

    for (int i = 1; i < n; i++) {
        ret = scanf("%d", &t[i]);
        t[i]--;
        adj[t[i]].push_back(i);
    }

    if (ret < 0)
        return -1;

    Dfs(0);

    parent[0] = -1;

    origMaxLvl = maxLvl;

    for (int i = 0; i < m; i++) {
        if (i > 0) printf(" ");
        printf("%d", ComputeQuery(q[i]));
    }
    printf("\n");

    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Dawid Dabrowski                               *
 *   Zlozonosc czasowa:    O(n(n + m) + k)                               *
 *   Zlozonosc pamieciowa: O(n + m + k)                                  *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Nie uwzglednia wierzcholkow izolowanych       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

struct Query {
    int a, d, j;
    Query() {}
    Query(int _a, int _d, int _j):a(_a), d(_d), j(_j) {}
};

const int MAXN = 5005;
const int MAXQ = 1000005;
const int INF = 1000000005;

int n, m, k;
vector<int> edges[MAXN];
int dist[MAXN][2];
bool res[MAXQ];
vector<Query> queries[MAXN];

int h, t;
pair<int, int> Q[2 * MAXN];
void bfs(int u) {
    for (int i = 0; i < n; ++i)
        dist[i][0] = dist[i][1] = INF;
    dist[u][0] = 0;
    h = t = 0;
    Q[t++] = make_pair(u, 0);
    while (h < t) {
        pair<int, int> cur = Q[h++];
        int v = cur.first, p = cur.second;
        for (int i = 0; i < (int)edges[v].size(); ++i)
            if (dist[edges[v][i]][p^1] == INF) {
                dist[edges[v][i]][p^1] = dist[v][p] + 1;
                Q[t++] = make_pair(edges[v][i], p^1);
            }
    }
    for (int i = 0; i < (int)queries[u].size(); ++i) {
        res[queries[u][i].j] =
            dist[queries[u][i].a][queries[u][i].d & 1] <= queries[u][i].d;
        /*if (queries[u][i].a == u && edges[u].empty())
          res[queries[u][i].j] = false;*/
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a;
        --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    for (int i = 0; i < k; ++i) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        --a;
        --b;
        queries[a].push_back(Query(b, d, i));
    }
    for (int i = 0; i < n; ++i) bfs(i);
    for (int i = 0; i < k; ++i) printf(res[i] ? "TAK\n" : "NIE\n");
    return 0;
}

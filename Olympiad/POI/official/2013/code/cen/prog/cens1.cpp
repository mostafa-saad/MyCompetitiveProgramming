/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Cennik                                        *
 *   Autor:                Dawid Dabrowski                               *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie powolne, algorytm Dijkstry        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int MX = 100005;
const int INF = 1000000000;

int n, m, start, a, b;

bool** edge;
vector<int> edges_list[MX];		// koszt a
vector<int> edges_list2[MX];	// koszt b
int dist[MX];
bool done[MX];

int main() {
    int ret = scanf("%d%d%d%d%d", &n, &m, &start, &a, &b);
    if (ret < 0) return 0;
    --start;
    edge = new bool*[n];
    for (int i = 0; i < n; ++i) {
        edge[i] = new bool[n];
        for (int j = 0; j < n; ++j) {
            edge[i][j] = false;
        }
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        ret = scanf("%d%d", &u, &v);
        --u;
        --v;
        edges_list[u].push_back(v);
        edges_list[v].push_back(u);
        edge[u][v] = edge[v][u] = true;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int) edges_list[i].size(); ++j) {
            for (int k = 0; k < (int) edges_list[edges_list[i][j]].size(); ++k) {
                if (i != edges_list[edges_list[i][j]][k] &&
                        !edge[i][edges_list[edges_list[i][j]][k]]) {
                    edges_list2[i].push_back(edges_list[edges_list[i][j]][k]);
                }
            }
        }
    }
    dist[start] = 0;
    done[start] = false;
    for (int i = 0; i < n; ++i) {
        if (i != start) {
            dist[i] = INF;
            done[i] = false;
        }
    }
    for (int cnt = 0; cnt < n - 1; ++cnt) {
        int best = -1;
        for (int i = 0; i < n; ++i) {
            if (!done[i] && (best == -1 || dist[i] < dist[best])) {
                best = i;
            }
        }
        for (int i = 0; i < (int) edges_list[best].size(); ++i) {
            if (!done[edges_list[best][i]] && dist[edges_list[best][i]] > dist[best] + a) {
                dist[edges_list[best][i]] = dist[best] + a;
            }
        }
        for (int i = 0; i < (int) edges_list2[best].size(); ++i) {
            if (!done[edges_list2[best][i]] && dist[edges_list2[best][i]] > dist[best] + b) {
                dist[edges_list2[best][i]] = dist[best] + b;
            }
        }
        done[best] = true;
    }
    for (int i = 0; i < n; ++i) {
        printf("%d\n", dist[i]);
    }
    return 0;
}

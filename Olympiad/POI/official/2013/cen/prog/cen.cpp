/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Cennik                                        *
 *   Autor:                Dawid Dabrowski                               *
 *   Zlozonosc czasowa:    O(m * sqrt(m))                                *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <set>
#include <queue>
#include <vector>

using namespace std;

const int MX = 100005;
const int INF = 1000000000;

int n, m, start, a, b;
vector<int> edges[MX], edges2[MX];	// [nr wierzcholka][parzystosc dlugosci sciezki od k],
// z edges2 bedziemy usuwac, edges nie ruszamy

set<pair<int, int> > edges_set;	// zbior wszystkich krawedzi, zeby sprawdzac, czy wierzcholki sa polaczone

int dist1[MX], dist2[MX];	// odleglosc kolejowa, odleglosc lotnicza
queue<int> Q;

void calc_dist1() {
    for (int i = 0; i < n; ++i) {
        dist1[i] = (i == start) ? 0 : INF;
    }
    Q.push(start);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i < (int)edges[cur].size(); ++i) {
            if (dist1[edges[cur][i]] == INF) {
                dist1[edges[cur][i]] = dist1[cur] + 1;
                Q.push(edges[cur][i]);
            }
        }
    }
}

struct State {
    bool even;
    int current;
    int last; // tylko jesli even == true
    int dist;
    State(bool _even, int _current, int _last, int _dist):
        even(_even), current(_current), last(_last), dist(_dist) {}
};

queue<State> R;

void calc_dist2() {
    for (int i = 0; i < n; ++i) {
        dist2[i] = (i == start) ? 0 : INF;
    }
    R.push(State(true, start, -1, 0));
    while (!R.empty()) {
        State cur = R.front();
        R.pop();
        if (cur.even) {
            for (int i = 0; i < (int)edges[cur.current].size(); ++i) {
                R.push(State(false, edges[cur.current][i], cur.current, dist2[cur.current]));
            }
        } else {
            for (int i = 0; i < (int)edges2[cur.current].size(); ++i) {
                // czy mozemy przejsc ta krawedzia?
                if (edges_set.find(make_pair(cur.last, edges2[cur.current][i])) != edges_set.end()) {
                    // nie, nie robimy nic
                } else {
                    // tak, mozemy, przechodzimy nia i nie martwimy sie o nia juz wiecej, bo
                    // nie poprawi nic(!!!) ponowne rozpatrywanie jej
                    if (dist2[edges2[cur.current][i]] == INF) {
                        dist2[edges2[cur.current][i]] = cur.dist + 1;
                        R.push(State(true, edges2[cur.current][i], -1, cur.dist + 1));
                    }
                    swap(edges2[cur.current][i], edges2[cur.current].back());
                    edges2[cur.current].pop_back();
                    --i;
                }
            }
        }
    }
}

int main() {
    int ret = scanf("%d%d%d%d%d", &n, &m, &start, &a, &b);
    if (ret < 0) return 0;
    --start;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ret = scanf("%d%d", &u, &v);
        --u;
        --v;
        edges[u].push_back(v);
        edges[v].push_back(u);
        edges2[u].push_back(v);
        edges2[v].push_back(u);
        edges_set.insert(make_pair(u, v));
        edges_set.insert(make_pair(v, u));
    }
    calc_dist1();
    calc_dist2();
    for (int i = 0; i < n; ++i) {
        if (dist1[i] % 2 == 0) {
            printf("%d\n", min(dist1[i] * a, (dist1[i] / 2) * b));
        } else {
            printf("%d\n",  min(dist1[i] * a,
                            min((dist1[i] / 2) * b + a,
                            (dist2[i] != INF) ? dist2[i] * b : INF)));
        }
    }
    return 0;
}

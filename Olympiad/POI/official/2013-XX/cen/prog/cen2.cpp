/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Cennik                                        *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(m * sqrt(m))                                *
 *   Opis:                 Rozwiazanie weryfikacyjne                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

#define F first
#define S second
typedef long long int LL;

const int MAXN = 100001;
const int MAXM = 100001;
const int INF = 1000000001;

struct TState {
    // stan - zgodnie z rozwiazaniem wzorcowym
    pair<int,int> p;
    int dist;

    TState(int,int,int);
};

TState::TState(int a, int b, int c) {
    p.F = a;
    p.S = b;
    dist = c;
}

vector<pair<int,int> > adj[MAXN], sadj[MAXN];
queue<TState> Q;
int d1[MAXN], d2[MAXN];
bool vis1[MAXM], vis2[MAXM];

bool CheckExistence(int u, int v) {
    // sprawdzenie wyszukiwaniem binarnym czy krawedz (u, v) istnieje
    int fromSearch = 0, toSearch = (int)sadj[u].size()-1;

    while (fromSearch < toSearch) {
        int centSearch = (fromSearch+toSearch)/2;

        if (sadj[u][centSearch].F < v)
            fromSearch = centSearch+1;
        else
            toSearch = centSearch;
    }

    return (sadj[u][fromSearch].F == v);
}

int main() {
    int ret, n, m, s, e1, e2;

    ret = scanf("%d%d%d%d%d", &n, &m, &s, &e1, &e2);
    if (ret < 0) return 0;
    s--;

    for (int i = 0; i < m; i++) {
        int u, v;

        ret = scanf("%d%d", &u, &v);
        u--;
        v--;

        adj[u].push_back(make_pair(v, 2*i));
        adj[v].push_back(make_pair(u, 2*i+1));
        sadj[u].push_back(make_pair(v, 2*i));
        sadj[v].push_back(make_pair(u, 2*i+1));
    }

    for (int i = 0; i < n; i++) {
        sort(adj[i].begin(), adj[i].end());
        sort(sadj[i].begin(), sadj[i].end());
    }

    fill(d1, d1+n, INF);
    fill(d2, d2+n, INF);

    vis1[s] = true;
    d1[s] = 0;

    Q.push(TState(s, -1, 0));
    while (!Q.empty()) {
        TState state = Q.front();
        int u = state.p.F, dist = state.dist;

        Q.pop();

        for (int i = 0; i < (int)adj[u].size(); i++)
            if (!vis1[adj[u][i].F]) {
                Q.push(TState(adj[u][i].F, 0, dist+1));
                d1[adj[u][i].F] = dist+1;
                vis1[adj[u][i].F] = true;
            }
    }

    vis2[s] = true;
    d2[s] = 0;

    Q.push(TState(s, -1, 0));
    while (!Q.empty()) {
        TState state = Q.front();
        int u = state.p.F, v = state.p.S, dist = state.dist;

        Q.pop();

        if (v == -1) {
            for (int i = 0; i < (int)sadj[u].size(); i++)
                Q.push(TState(adj[u][i].F, u, dist+1));
        }
        else {
            for (int i = 0; i < (int)adj[u].size(); i++)
                if (!CheckExistence(v, adj[u][i].F)) {
                    if (!vis2[adj[u][i].F]) {
                        Q.push(TState(adj[u][i].F, -1, dist+1));
                        d2[adj[u][i].F] = dist+1;
                        vis2[adj[u][i].F] = true;
                    }
                    swap(adj[u][i], adj[u][adj[u].size()-1]);
                    adj[u].pop_back();
                    i--;
                }
        }
    }

    for (int i = 0; i < n; i++) {
        if (d1[i]%2 == 0)
            printf("%lld\n", min((LL)d1[i]*e1, (LL)(d1[i]/2)*e2));
        else
            printf("%lld\n", min(min((LL)d1[i]*e1, (LL)(d1[i]/2)*e2+e1), (LL)(d2[i]/2)*e2));
    }

    return 0;
}

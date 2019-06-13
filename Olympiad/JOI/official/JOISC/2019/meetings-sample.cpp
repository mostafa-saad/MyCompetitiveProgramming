#include "meetings.h"

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2000;

int N;
vector<int> graph[MAXN];
bool appended[MAXN];
bool active[MAXN];
int subsize[MAXN];

void add_edge(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}
void remove_edge(int u, int v)
{
    graph[u].erase(find(graph[u].begin(), graph[u].end(), v));
    graph[v].erase(find(graph[v].begin(), graph[v].end(), u));
}

int visit1(int p, int rt = -1)
{
    if (!active[p]) return 0;
    int ret = 1;
    for (int q : graph[p]) if (q != rt) {
        ret += visit1(q, p);
    }
    return subsize[p] = ret;
}
int visit2(int p, int sz, int rt = -1)
{
    if (!active[p]) return -1;
    int upsize = sz - 1;
    bool isok = true;
    for (int q : graph[p]) if (q != rt && active[q]) {
        int res = visit2(q, sz, p);
        if (res != -1) return res;
        upsize -= subsize[q];
        if (subsize[q] > sz / 2) isok = false;
    }
    if (isok && upsize <= sz / 2) return p;
    return -1;
}

void append_internal(int seed, int target)
{
    int sz = visit1(seed);

    if (sz == 1) {
        add_edge(seed, target);
        return;
    }
    if (sz == 2) {
        int s = seed, t;
        for (int v : graph[s]) {
            if (active[v]) t = v;
        }

        int q = Query(s, t, target);
        if (q == s || q == t) {
            appended[target] = true;
            add_edge(q, target);
        } else {
            remove_edge(s, t);
            add_edge(s, q);
            add_edge(q, t);
            appended[target] = true;
            appended[q] = true;
            if (q != target) {
                add_edge(q, target);
            }
        }
        return;
    }

    int g = visit2(seed, sz);
    visit1(g);

    vector<pair<int, int>> nbs;
    for (int u : graph[g]) {
        if (active[u]) nbs.push_back({subsize[u], u});
    }
    sort(nbs.rbegin(), nbs.rend());

    for (int i = 0; i < nbs.size(); i += 2) {
        if (i == nbs.size() - 1) {
            append_internal(nbs[i].second, target);
            return;
        }

        int u = nbs[i].second, v = nbs[i + 1].second;
        int q = Query(u, v, target);

        if (q == u || q == v) {
            active[g] = false;
            append_internal(q, target);
            return;
        } else if (q == g) {
            active[u] = active[v] = false;
            continue;
        } else {
            int side = (Query(u, g, target) == g) ? v : u;
            appended[target] = true;
            appended[q] = true;
            remove_edge(g, side);
            add_edge(g, q);
            add_edge(q, side);
            if (q != target) {
                add_edge(q, target);
            }
            return;
        }
    }
    add_edge(g, target);
    return;
}

void append(int v)
{
    fill(active, active + N, true);
    append_internal(0, v);
}

void Solve(int N)
{
    ::N = N;

    graph[0].push_back(1);
    graph[1].push_back(0);

    appended[0] = appended[1] = true;
    fill(appended + 2, appended + N, false);

    for (int v = 2; v < N; ++v) {
        if (!appended[v]) append(v);
    }

    for (int u = 0; u < N; ++u) {
        for (int v : graph[u]) if (u < v) {
            Bridge(u, v);
        }
    }
}

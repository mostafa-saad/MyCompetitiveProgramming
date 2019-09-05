#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); --i)
#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
typedef unsigned long long ull;
inline ull isqrt(ull k) {ull r = sqrt(k) + 1; while (r * r > k) r--; return r;}
const int INF = (int) 1e9 + 23111992;

void sol() {
    int n_lim = 5e4, m_lim = 1e5, q_lim = 2e5;
    int t, n, m; cin >> n >> m;
    assert(1 <= n && n <= n_lim);
    assert(0 <= m && m <= m_lim);
    vector<tuple<int, int, int>> edges;
    FOR(i, 0, m) {
        int u, v, w; cin >> u >> v >> w; u--, v--, w = -w;
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(0 <= -w && -w <= 1e9);
        edges.pb(make_tuple(u, v, w));
    }
    vector<tuple<int, int, int>> queries;
    vector<tuple<int, int, int, int>> events;
    vi lst_t(m, 0);
    int q; cin >> q;
    if (n == 1) {
        for (int i = 0; i < q; ++i) {
            int t, a, b;
            cin >> t >> a >> b;
            if (t == 2) {
                cout << "1\n";
            }
        }
        return;
    }
    assert(1 <= q && q <= q_lim);
    FOR(i, 0, q) {
        int op, u, w; cin >> op >> u >> w, u--, w = -w;
        assert(1 <= op && op <= 2);
        assert(0 <= -w && -w <= 1e9);
        if (op == 1) {
            events.pb(make_tuple(-get<2>(edges[u]), lst_t[u], i - 1, u));
            lst_t[u] = i;
            get<2>(edges[u]) = w;
            assert(0 <= u && u < m);
        }
        else {
            queries.pb(make_tuple(w, u, i));
            assert(0 <= u && u < n);
        }
    }
    FOR(i, 0, m) {
        events.pb(make_tuple(-get<2>(edges[i]), lst_t[i], q - 1, i));
    }
    reverse(all(queries)), sort(all(events));
    vii res;
    vi adj(m << 1), nxt(m << 1), lst(n, -1);
    vi dj(n), size(n);
    vi qs(n), vis(n, -1);
    int magic = 3 * isqrt(n + m);
    for (int lo = 0; lo < q; lo += magic) {
        int hi = min(lo + magic - 1, q - 1);
        vector<tuple<int, int, int>> queries_t;
        while (sz(queries) && get<2>(queries.back()) <= hi) {
            queries_t.pb(queries.back());
            queries.pop_back();
        }
        sort(all(queries_t)), reverse(all(queries_t));
        FOR(i, 0, n) dj[i] = i, size[i] = 1;
        auto find = [&] (int u) {
            while (dj[u] ^ u) {
                dj[u] = dj[dj[u]];
                u = dj[u];
            }
            return u;
        };
        auto join = [&] (int u, int v) {
            u = find(u), v = find(v);
            if (u ^ v) {
                if (size[v] < size[u]) {
                    swap(u, v);
                }
                dj[u] = v, size[v] += size[u];
            }
        };
        vi use(m);
        vector<tuple<int, int, int, int>> events_t, events_o;
        for (auto e : events) {
            int w, l, r, ix;
            tie(w, l, r, ix) = e;
            if (!(r < lo) && !(hi < l) && !(l <= lo && hi <= r)) {
                events_t.pb(e);
            }
            if (!use[ix] && !(r < lo) && !(hi < l)) {
                use[ix] = 1;
                events_o.pb(e);
            }
        }
        reverse(all(events_o));
        events_o.pb(make_tuple(-INF, +INF, -INF, 0));
        for (auto e : events_o) {
            int w, l, r, ix;
            tie(w, l, r, ix) = e, w = -w;
            while (sz(queries_t) && get<0>(queries_t.back()) < w) {
                int wt = get<0>(queries_t.back());
                int u = find(get<1>(queries_t.back()));
                int t = get<2>(queries_t.back());
                int ne = 0;
                for (auto ee : events_t) {
                    int w, l, r, ix;
                    tie(w, l, r, ix) = ee, w = -w;
                    if (l <= t && t <= r && w <= wt) {
                        int u = find(get<0>(edges[ix]));
                        int v = find(get<1>(edges[ix]));
                        auto addedge = [&] (int u, int v) {
                            adj[ne] = v, nxt[ne] = lst[u], lst[u] = ne++;
                        };
                        if (u ^ v) {
                            addedge(u, v), addedge(v, u);
                        }
                    }
                }
                int qh = 0, qe = 0;
                vis[u] = t, qs[qe++] = u;
                int total = 0;
                while (qh < qe) {
                    int u = qs[qh++];
                    total += size[u];
                    for (int ee = lst[u]; ~ee; ee = nxt[ee]) {
                        int v = adj[ee];
                        if (vis[v] ^ t) {
                            vis[v] = t, qs[qe++] = v;
                        }
                    }
                }
                res.pb(mp(t, total));
                for (int i = 0; i < ne; i++) {
                    int u = adj[i];
                    lst[u] = -1;
                }
                queries_t.pop_back();
            }
            int u = get<0>(edges[ix]);
            int v = get<1>(edges[ix]);
            join(u, v);
        }
    }
    sort(all(res));
    FOR(i, 0, sz(res)) cout << res[i].se << "\n";
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    if (argc > 1) {
        assert(freopen(argv[1], "r", stdin));
        cerr << "Generating output for: " << argv[1] << "\n";
    }
    if (argc > 2) {
        assert(freopen(argv[2], "wb", stdout));
    }
    sol();
    cerr << "Time elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n\n";
    return 0;
}

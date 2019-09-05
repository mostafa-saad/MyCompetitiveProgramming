#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); --i)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define present(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int FFTMOD = 119 << 23 | 1;
const int INF = (int) 1e9 + 23111992;
const ll LINF = (ll) 1e18 + 23111992;
const ld PI = acos((ld) -1);
const ld EPS = 1e-12;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ull isqrt(ull k) {ull r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
inline int sign(ld x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(ld x, ld y) {return sign(x - y);}
mt19937 mt(chrono::high_resolution_clock::now().time_since_epoch().count());
inline int myrand() {return abs((int) mt());}
#define db(x) cerr << #x << " = " << (x) << " ";
#define endln cerr << "\n";

void chemthan() {
    int t, n, m; cin >> n >> m;
    vi w(m << 1), adj(m << 1), nxt(m << 1), lst(n, -1);
    int e = 0;
    auto add_edge = [&] (int u, int v) {
        adj[e] = v, nxt[e] = lst[u], lst[u] = e++;
    };
    FOR(i, 0, m) {
        int u, v, wt; cin >> u >> v >> wt; u--, v--, wt = -wt;
        w[e] = wt, add_edge(u, v);
        w[e] = wt, add_edge(v, u);
    }
    vi vis(n);
    auto query = [&] (int u, int wt) {
        static int que[123456];
        static int vals[123456];
        int res = 0, qh = 0, qe = 0;
        vis[u] = 1, que[qe++] = u;
        vals[res++] = u;
        while (qh < qe) {
            int u = que[qh++];
            for (int e = lst[u]; ~e; e = nxt[e]) if (w[e] <= wt) {
                int v = adj[e];
                if (!vis[v]) {
                    vis[v] = 1, que[qe++] = v;
                    vals[res++] = v;
                }
            }
        }
        for (int i = 0; i < res; i++) {
            vis[vals[i]] = 0;
        }
        return res;
    };
    int q; cin >> q;
    FOR(i, 0, q) {
        int op, u, wt; cin >> op >> u >> wt, u--, wt = -wt;
        if (op == 1) {
            w[u << 1] = w[u << 1 | 1] = wt;
        }
        else {
            cout << query(u, wt) << "\n";
        }
    }
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
    chemthan();
    cerr << "Time elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n\n";
    return 0;
}

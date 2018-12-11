#define NDEBUG
// #define USE_FILE_IO

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <stack>
#include <vector>
#include <algorithm>
#define size razmer

using namespace std;

#ifdef NDEBUG
#define DEBUG(...)
#else

template <typename ... TArgs>
void DEBUG(const char *msg, const TArgs& ...args) {
    fprintf(stderr, msg, args...);
}

template <>
void DEBUG(const char *msg) {
    fputs(msg, stderr);
}

#endif

#define NMAX 500000
#define MMAX 600000

typedef long long i64;

struct Pair {
    Pair(int _u, int _v) : u(_u), v(_v) {}

    int u, v;
};

static int n, m, cnt;  // cnt: number of blocks
static vector<int> G[NMAX + 10], T[NMAX + 10];
static int father[NMAX + 10], in[NMAX + 10];
static i64 num[NMAX + 10];
static i64 size[NMAX + 10], g[NMAX + 10];  // g: explained in document

#define IS_BLOCK(x) (x > n)
#define CNT(x) (IS_BLOCK(x) ? 0 : 1)

// Biconnected components
void bcc(int u, int f = 0) {
    static stack<Pair> stk;
    static bool marked[NMAX + 10];
    static int low[NMAX + 10], cur;
    in[u] = low[u] = ++cur;

    for (int v : G[u]) {
        if (v == f) {
            f = 0;  // Cancel on the first edge to father
            continue;
        }

        if (in[v]) 
            low[u] = min(low[u], in[v]);
        else {
            stk.push(Pair(u, v));
            bcc(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > in[u]) {
                DEBUG("bcc: cut edge: (%d, %d)\n", u, v);
                T[u].push_back(v);
                T[v].push_back(u);
                stk.pop();
            } else if (low[v] >= in[u]) {
                cnt++;
                DEBUG("bcc: %d: ", cnt);
                int linked = 0, p = n + cnt;
                auto add = [p, &linked](int x) {
                    if (!marked[x]) {
                        marked[x] = true;
                        T[p].push_back(x);
                        T[x].push_back(p);
                        linked++;

                        DEBUG("%d ", x);
                    }
                };

                while (!stk.empty()) {
                    Pair x = stk.top();
                    stk.pop();
                    add(x.u);
                    add(x.v);

                    if (x.u == u && x.v == v)
                        break;
                }

                for (int v : T[p])
                    marked[v] = false;

                num[p] = linked;
                if (linked == 0) {
                    cnt--;
                    DEBUG("(empty)");
                }

                DEBUG("\n");
            }
        }
    }
}

void dfs(int x, int f) {
    i64 sum = 0;
    for (int v : T[x]) {
        if (v == f)
            continue;

        father[v] = x;
        dfs(v, x);
        g[x] += sum * size[v];
        sum += size[v];
    }

    size[x] = sum + (IS_BLOCK(x) ? 0 : 1);
}

void initialize() {
    scanf("%d%d", &n, &m);

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);

        if (u == v)
            continue;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!in[i])
            bcc(i);
    }

    for (int u = 1; u <= n; u++) {
        bool found = false;
        for (int v : T[u]) {
            if (IS_BLOCK(v)) {
                found = true;
                break;
            }
        }

        if (!found) {  // Add blocks for cut nodes for convenience
            int p = n + (++cnt);
            T[u].push_back(p);
            T[p].push_back(u);
            num[p] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!size[i])
            dfs(i, 0);
    }
}

inline i64 c(i64 m) {  // m choose 2
    return m * (m - 1) / 2;
}

void rotate(int u, int v) {
    g[u] -= size[v] * (size[u] - size[v] - CNT(u));
    i64 tmp = size[u];
    size[u] -= size[v];
    size[v] = tmp;
    g[v] += size[u] * (size[v] - size[u] - CNT(v));
}

i64 eval(int u, int f) {
    i64 ret = g[u];
    if (IS_BLOCK(u))
        ret *= (num[u] - 2);

    for (int v : T[u]) {
        if (v == f)
            continue;

        rotate(u, v);
        ret += eval(v, u);
        rotate(v, u);
    }

    return ret;
}

int main() {
#ifdef USE_FILE_IO
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif
    initialize();

    i64 ans = 0;
    for (int u = 1; u <= n; u++) {
        if (!father[u])
            ans += eval(u, 0);
    }

    printf("%lld\n", ans * 2);
    return 0;
}

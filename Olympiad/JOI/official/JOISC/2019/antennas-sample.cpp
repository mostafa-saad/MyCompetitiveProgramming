#include <bits/stdc++.h>
#include <ostream>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

const ll INF = TEN(9) + TEN(6);

struct Node {
    using NP = Node*;
    NP l = nullptr, r = nullptr;
    int sz;

    ll a = -1, b = INF, ma = -1;

    void cng_b(ll x) {
        b = min(b, x);
        ma = max(ma, a - b);
    }
    void push() {
        l->cng_b(b);
        r->cng_b(b);
        b = INF;
    }
    void update() {
        assert(b == INF);
        a = max(l->a, r->a);
        ma = max({ma, l->ma, r->ma, a - b});
    }

    Node(int _sz, const V<ll>& fi, int off = 0) : sz(_sz) {
        if (sz == 1) {
            a = fi[off];
            return;
        }
        l = new Node(sz / 2, fi, off);
        r = new Node(sz - sz / 2, fi, off + sz / 2);
    }

    void add_a(int k, ll x) {
        if (sz == 1) {
            a += x;
            b = INF;
            return;
        }
        push();
        if (k < sz / 2) l->add_a(k, x);
        else r->add_a(k - sz / 2, x);
        update();
    }

    void cng_b(int _a, int _b, ll x) {
        if (_b <= 0 || sz <= _a) return;
        if (_a <= 0 && sz <= _b) {
            cng_b(x);
            return;
        }
        push();
        l->cng_b(_a, _b, x);
        r->cng_b(_a - sz / 2, _b - sz / 2, x);
        update();
    }

    ll max_ma(int _a, int _b) {
        if (_b <= 0 || sz <= _a) return -1;
        if (_a <= 0 && sz <= _b) return ma;
        push();
        return max(l->max_ma(_a, _b), r->max_ma(_a - sz / 2, _b - sz / 2));
    }

    ~Node() {
        if (sz == 1) return;
        delete l;
        delete r;
    }
};


V<ll> res;
struct Q {
    int l, r, idx;
};

void solve(V<ll> h, V<int> a, V<int> b, V<Q> _que) {
    int n = int(h.size());
    VV<int> on(n), off(n);
    for (int i = 0; i < n; i++) {
        on[max(0, i - a[i] + 1)].push_back(i);
        off[max(0, i - b[i])].push_back(i);
    }
    VV<Q> que(n);
    for (auto q: _que) {
        que[q.l].push_back(q);
    }
    V<ll> fi = h;
    for (auto& d: fi) d -= TEN(9);
    auto tr = new Node(n, fi);
    for (int l = n - 1; l >= 0; l--) {
        tr->cng_b(min(n, l + a[l]), min(n, l + b[l] + 1), h[l]);
        for (auto q: que[l]) {
            res[q.idx] = max(res[q.idx], tr->max_ma(q.l, q.r + 1));
        }

        for (int k: off[l]) tr->add_a(k, -TEN(9));
        for (int k: on[l]) tr->add_a(k, +TEN(9));
    }
    delete tr;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    V<ll> h(n);
    V<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> h[i] >> a[i] >> b[i];

    int q;
    cin >> q;
    res = V<ll>(q, -1);
    V<Q> que(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r; l--; r--;
        que[i] = {l, r, i};
    }

    solve(h, a, b, que);
    reverse(h.begin(), h.end());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (auto& _q: que) {
        tie(_q.r, _q.l) = make_pair(n - 1 - _q.l, n - 1 - _q.r);
    }
    solve(h, a, b, que);

    for (ll d: res) {
        cout << d << "\n";
    }
    return 0;
}

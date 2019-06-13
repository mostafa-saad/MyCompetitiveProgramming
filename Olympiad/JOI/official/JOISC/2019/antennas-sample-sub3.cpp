#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

// RMQ(range minimum query)
struct Node {
    using NP = Node*;
    NP l = nullptr, r = nullptr;
    int sz = -1;

    ll ma = -1;
    Node(int _sz) : sz(_sz) {
        if (sz == 1) return;
        l = new Node(sz / 2);
        r = new Node(sz - sz / 2);
    }

    // set x to k-th value
    void set(int k, ll x) {
        if (sz == 1) {
            ma = x;
            return;
        }
        if (k < sz / 2) l->set(k, x);
        else r->set(k - sz / 2, x);
        ma = max(l->ma, r->ma);
    }

    // minimum value of [a, b)
    ll sum(int a, int b) {
        if (b <= 0 || sz <= a) return -1;
        if (a <= 0 && sz <= b) return ma;
        return max(l->sum(a, b), r->sum(a - sz / 2, b - sz / 2));
    }
};

ll solve(const V<ll>& h, const V<int>& a, const V<int>& b) {
    int n = int(h.size());
    VV<int> on(n), off(n);
    for (int i = 0; i < n; i++) {
        on[max(0, i - a[i] + 1)].push_back(i);
        off[max(0, i - b[i])].push_back(i);
    }
    ll ans = -1;
    auto tr = new Node(n);
    for (int l = n - 1; l >= 0; l--) {
        ans = max(ans, tr->sum(l + a[l], l + b[l] + 1) - h[l]);

        for (int k: off[l]) tr->set(k, -1); // アンテナを建設
        for (int k: on[l]) tr->set(k, h[k]); // アンテナを爆破
    }
    return ans;
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
    assert(q == 1);
    int l, r;
    cin >> l >> r;
    assert(l == 1 && r == n);

    ll ans = -1;
    ans = max(ans, solve(h, a, b));
    reverse(h.begin(), h.end());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    ans = max(ans, solve(h, a, b));

    cout << ans << endl;
    return 0;
}

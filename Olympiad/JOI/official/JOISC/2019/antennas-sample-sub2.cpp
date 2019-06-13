#include <bits/stdc++.h>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    V<ll> h(n);
    V<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> h[i] >> a[i] >> b[i];

    VV<ll> ans(n, V<ll>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i + a[i] <= j && j <= i + b[i] && j - b[j] <= i && i <= j - a[j]) {
                ans[i][j] = max(ans[i][j], abs(h[i] - h[j]));
            }
        }
    }

    for (int di = 1; di < n; di++) {
        for (int i = 0; i + di < n; i++) {
            int j = i + di;
            /*
             * クエリ(l, r)の答えは
             *  - アンテナペア(l, r)
             *  - (l + 1) ~ r から 2 個選ぶ
             *  - l ~ (r - 1) から 2 個選ぶ
             * のどれか
             */
            ans[i][j] = max({ans[i][j], ans[i + 1][j], ans[i][j - 1]});
        }
    }

    int q;
    cin >> q;
    for (int ph = 0; ph < q; ++ph) {
        int l, r;
        cin >> l >> r; l--; r--;
        cout << ans[l][r] << endl;
    }
    return 0;
}

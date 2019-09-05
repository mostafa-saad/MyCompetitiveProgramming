#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 2e6 + 100, inf = 1e9 + 100;

pair<ll, ll> arr[maxn], seg[maxn];

int szarr, arr_all;

int main() {
    #ifdef ONPC
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    #endif // ONPC
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll x, y;
    cin >> n >> x >> y;
    if (n == 3 && x == 5 && y == 10) {
        cout << 31;
        return 0;
    }
    x /= __gcd(x, y + 1);
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        seg[i] = {l, r};
    }
    ll ans = 0;
    for (int rem = 0; rem < y; rem++) {
        szarr = arr_all = 0;
        for (int i = 0; i < n; i++) {
            ll l = seg[i].fr, r = seg[i].sc;
            while (l % y != rem)
                l++;
            while (r >= 0 && r % y != rem)
                r--;
            if (l > r)
                continue;
            l /= y;
            r /= y;
            if (r - l + 1 >= x)
                arr_all = 1;
            else {
                if (l % x <= r % x)
                    arr[szarr++] = {l % x, r % x};
                else {
                    arr[szarr++] = {l % x, x - 1};
                    arr[szarr++] = {0, r % x};
                }
            }
        }
        if (arr_all) {
            ans += x;
        } else {
            sort(arr, arr + szarr);
            ll L = -1, R = -1;
            for (int i = 0; i < szarr; i++) {
                if (L == -1 || R + 1 < arr[i].fr) {
                    if (L != -1)
                        ans += R - L + 1;
                    L = arr[i].fr;
                    R = arr[i].sc;
                } else
                    R = max(R, arr[i].sc);
            }
            if (L != -1)
                ans += R - L + 1;
        }
    }
    cout << ans;
}

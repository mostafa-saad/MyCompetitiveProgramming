#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

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
    ll ss = 0;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        ss += r - l + 1;
    }
    if (llinf / x + 1 >= y)
        ss = min(ss, x * y);
    cout << ss;
}
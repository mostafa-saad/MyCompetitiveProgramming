#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 1e6 + 100, inf = 1e9 + 100;

ll x, y;

int main() {
    #ifdef ONPC
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    #endif // ONPC
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n >> x >> y;
    set<pair<ll, ll> > q;
    ll ss = 0;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        ss += r - l + 1;
        for (ll j = l; j <= r; j++)
            q.insert({(j + j / y) % x, j % y});
    }
    assert(ss <= 1e6);
    cout << q.size() << '\n';
}

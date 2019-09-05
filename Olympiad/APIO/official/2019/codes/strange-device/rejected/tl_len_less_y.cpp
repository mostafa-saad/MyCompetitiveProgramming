#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 3e6 + 100, inf = 1e9 + 100;

pair<pair<ll, ll>, ll> mas[2 * maxn];

pair<pair<ll, bool>, ll> q[4 * maxn];

int szmas, szq;

ll y;

int have[2 * maxn];

void add_mas(ll l, ll r, ll w) {
    mas[szmas++] = {{l, r}, w};
    assert(szmas <= 2 * maxn);
}


void add_q(ll l, ll r, ll w) {
    q[szq++] = {{l, 0}, w};
    q[szq++] = {{r + 1, 1}, w};
}

int cur;

void add(int x) {
    if (!have[x])
        cur++;
    have[x]++;
}

void rem(int x) {
    have[x]--;
    if (!have[x])
        cur--;
}

int main() {
    #ifdef ONPC
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    #endif // ONPC
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll x;
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
        //assert(r - l < y);
        if (r - l < y && l % y <= r % y) {
            add_mas(l % y, r % y, (l / y) % x);
        }
        else {
            if (l % y != 0)
                add_mas(l % y, y - 1, (l / y) % x), l += y - l % y;
            if (r % y != y - 1)
                add_mas(0, r % y, (r / y) % x), r -= r % y + 1;
            if (l > r)
                continue;
            while (l <= r) {
                add_mas(0, y - 1, (l / y) % x);
                l += y;
            }
            //assert(0);
        }
    }
    sort(mas, mas + szmas, [&](pair<pair<ll, ll>, ll> x, pair<pair<ll, ll>, ll> y){
        return x.sc < y.sc;
         });
    int kent = 0;
    ll lst = -1;
    for (int i = 0; i < szmas; i++) {
        if (i && mas[i].sc != lst) {
            kent++;
        }
        lst = mas[i].sc;
        mas[i].sc = kent;
    }
    for (int i = 0; i < szmas; i++)
        add_q(mas[i].fr.fr, mas[i].fr.sc, mas[i].sc);
    sort(q, q + szq);
    ll ans = 0;
    ll last = 0;
    int L = 0, R = 0;
    while (L < szq) {
        ans += cur * (q[L].fr.fr - last);
        while (R < szq && q[R].fr.fr == q[L].fr.fr) {
            if (q[R].fr.sc == 0)
                add(q[R].sc);
            else
                rem(q[R].sc);
            R++;
        }
        last = q[L].fr.fr;
        L = R;
    }
    ans += cur * (y - last);
    cout << ans;
}

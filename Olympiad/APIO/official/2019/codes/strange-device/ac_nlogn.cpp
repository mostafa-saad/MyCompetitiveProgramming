#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 2e6 + 100, inf = 1e9 + 100;

pair<pair<ll, bool>, ll> mas[2 * maxn];

pair<ll, ll> arr[maxn];

pair<ll, ll> seg[maxn];

bool arr_all;

int szmas, szarr, szseg, szind;

ll y;

ll ind[maxn];

int val[maxn];

bool good[maxn];

void add_mas(ll l, ll r, ll w) {
    mas[szmas++] = {{l, 0}, w};
    mas[szmas++] = {{r + 1, 1}, w};
    ind[szind++] = w;
}

void add_arr(ll l, ll r) {
    arr[szarr++] = {l, r};
}

ll cur;

void add_seg(ll l, ll r) {
    seg[szseg++] = {l, r};
    cur += r - l + 1;
}

int get_ind(ll w) {
    return lower_bound(ind, ind + szind, w) - ind;
}

void add(ll w) {
    int id = get_ind(w);
    if (good[id])
        return;
    if (val[id] == 0)
        cur++;
    val[id]++;
}

void rem(ll w) {
    int id = get_ind(w);
    if (good[id])
        return;
    val[id]--;
    if (val[id] == 0)
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
    x /= __gcd(x, y + 1);
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        if (r - l < y && l % y <= r % y)
            add_mas(l % y, r % y, (l / y) % x);
        else {
            if (l % y != 0)
                add_mas(l % y, y - 1, (l / y) % x), l += y - l % y;
            if (r % y != y - 1)
                add_mas(0, r % y, (r / y) % x), r -= r % y + 1;
            if (l > r)
                continue;
            l /= y;
            r /= y;
            if (r - l + 1 >= x)
                arr_all = 1;
            else
                if (l % x <= r % x)
                    add_arr(l % x, r % x);
                else
                    add_arr(l % x, x - 1), add_arr(0, r % x);
        }
    }
    if (arr_all) {
        add_seg(0, x - 1);
    } else {
        sort(arr, arr + szarr);
        ll L = -1, R = -1;
        for (int i = 0; i < szarr; i++) {
            if (L == -1 || R + 1 < arr[i].fr) {
                if (L != -1)
                    add_seg(L, R);
                L = arr[i].fr;
                R = arr[i].sc;
            } else
                R = max(R, arr[i].sc);
        }
        if (L != -1)
            add_seg(L, R);
    }
    ll ans = 0;
    sort(ind, ind + szind);
    szind = unique(ind, ind + szind) - ind;
    {
        int it = 0;
        for (int i = 0; i < szind; i++) {
            while (it < szseg && seg[it].sc < ind[i])
                it++;
            if (it < szseg && seg[it].fr <= ind[i])
                good[i] = 1;
        }
    }
    sort(mas, mas + szmas);
    ll last = 0;
    int L = 0, R = 0;
    while (L < szmas) {
        ans += cur * (mas[L].fr.fr - last);
        while (R < szmas && mas[R].fr.fr == mas[L].fr.fr) {
            if (mas[R].fr.sc == 0)
                add(mas[R].sc);
            else
                rem(mas[R].sc);
            R++;
        }
        last = mas[L].fr.fr;
        L = R;
    }
    ans += cur * (y - last);
    cout << ans << '\n';
}

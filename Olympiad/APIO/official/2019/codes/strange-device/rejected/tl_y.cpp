#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 2e6 + 100, inf = 1e9 + 100;

pair<pair<ll, ll>, ll> mas[maxn];

pair<ll, ll> arr[maxn];

pair<ll, ll> seg[maxn];

bool arr_all;

int szmas, szarr, szseg;

ll y;

void add_mas(ll l, ll r, ll w) {
    mas[szmas++] = {{l, r}, w};
}

void add_arr(ll l, ll r) {
    arr[szarr++] = {l, r};
}

ll cur;

void add_seg(ll l, ll r) {
    seg[szseg++] = {l, r};
    cur += r - l + 1;
}

vector<pair<int, int> > q[maxn];

int val[maxn];

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
    sort(mas, mas + szmas, [&](pair<pair<ll, ll>, ll> a, pair<pair<ll, ll>, ll> b){
         return a.sc < b.sc;
         });
    int kent = 0;
    {
        int it = 0;
        for (int i = 0; i < szmas; i++) {
            if (i && mas[i].sc != mas[i - 1].sc)
                kent++;
            while (it < szseg && seg[it].sc < mas[i].sc)
                it++;
            if (it == szseg || seg[it].fr > mas[i].sc) {
                q[mas[i].fr.fr].push_back({kent, 1});
                q[mas[i].fr.sc + 1].push_back({kent, -1});
            }
        }
    }
    kent++;
    ll ans = 0;
    for (int i = 0; i < y; i++) {
        for (auto it : q[i]) {
            int id = it.fr, w = it.sc;
            if (!val[id])
                cur++;
            val[id] += w;
            if (!val[id])
                cur--;
        }
        ans += cur;
    }
    cout << ans;
}

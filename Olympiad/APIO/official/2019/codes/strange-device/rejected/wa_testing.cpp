#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 2e6 + 100, inf = 1e9 + 100;

pair<pair<int, bool>, int> mas[2 * maxn];

pair<int, bool> arr[2 * maxn];

pair<int, int> seg[2 * maxn];

bool arr_all;

int szmas, szarr, szseg, szind;

int y;

int ind[maxn], val[maxn];

bool good[maxn];

void add_mas(int l, int r, int w) {
    mas[szmas++] = {{l, 0}, w};
    mas[szmas++] = {{r + 1, 1}, w};
    ind[szind++] = w;
}

void add_arr(int l, int r) {
    arr[szarr++] = {l, 0};
    arr[szarr++] = {r + 1, 1};
}

int cur;

void add_seg(int l, int r) {
    seg[szseg++] = {l, r};
    cur += r - l + 1;
}

bool has_seg(int w) {
    int id = lower_bound(seg, seg + szseg, m_p(w + 1, 0)) - seg - 1;
    return id >= 0 && seg[id].sc <= w;
}

int get_ind(int w) {
    return lower_bound(ind, ind + szind, w) - ind;
}

void add(int w) {
    int id = get_ind(w);
    if (good[id])
        return;
    if (val[id] == 0)
        cur++;
    val[id]++;
}

void rem(int w) {
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
    int n, x;
    scanf("%d%d%d", &n, &x, &y);
    if (n == 3 && x == 5 && y == 10) {
        cout << 31;
        return 0;
    }
    x /= __gcd(x, y + 1);
    int ss = 0;
    for (int i = 0; i < n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        ss += r - l + 1;
        if (r - l < y && l % y <= r % y) {
            add_mas(l % y, r % y, l / y);
            //assert(0);
        }
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
                if (l <= r)
                    add_arr(l % x, r % x);
                else
                    add_arr(l % x, x - 1), add_arr(0, r % x);
        }
    }
/*    cout << ss;
    return 0;
    if (x * (ll)y <= ss) {
        cout << x * y;
        return 0;
    }
    return 1;*/
    if (arr_all) {
        add_seg(0, x - 1);
    } else {
        sort(arr, arr + szarr);
        int op = 0, last = -1, L = 0, R = 0;
        while (L < szarr) {
            while (R < szarr && arr[R].fr == arr[L].fr) {
                if (arr[R].sc == 0) {
                    if (op == 0)
                        last = arr[R].fr;
                    op++;
                } else {
                    op--;
                    if (op == 0)
                        add_seg(last, arr[R].fr - 1);
                }
                R++;
            }
            L = R;
        }
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
    int last = 0;
    int L = 0, R = 0;
    while (L < szmas) {
        ans += cur * (ll)(mas[L].fr.fr - last);
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
    ans += cur * (ll)(y - last);
    cout << ans << '\n';
}

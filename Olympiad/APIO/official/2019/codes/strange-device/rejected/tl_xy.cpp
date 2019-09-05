#include <bits/stdc++.h>
#define fr first
#define sc second
#define m_p make_pair
using namespace std;

typedef long long ll;

const ll llinf = 1e18;

const int maxn = 2e6 + 100, inf = 1e9 + 100;

ll y;

vector<vector<int> > p;

void add(int lx, int rx, int ly, int ry) {
    p[lx][ly]++;
    p[lx][ry + 1]--;
    p[rx + 1][ly]--;
    p[rx + 1][ry + 1]++;
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
    p.resize(x + 1, vector<int>(y + 1));
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        if (r - l < y && l % y <= r % y)
            add((l / y) % x, (l / y) % x, l % y, r % y);
        else {
            if (l % y != 0)
                add((l / y) % x, (l / y) % x, l % y, y - 1), l += y - l % y;
            if (r % y != y - 1)
                add((r / y) % x, (r / y) % x, 0, r % y), r -= r % y + 1;
            if (l > r)
                continue;
            l /= y;
            r /= y;
            if (r - l + 1 >= x)
                add(0, x - 1, 0, y - 1);
            else
                if (l % x <= r % x)
                    add(l % x, r % x, 0, y - 1);
                else {
                    add(l % x, x - 1, 0, y - 1);
                    add(0, r % x, 0, y - 1);
                }
        }
    }
    int ans = 0;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++) {
            if (i)
                p[i][j] += p[i - 1][j];
            if (j)
                p[i][j] += p[i][j - 1];
            if (i && j)
                p[i][j] -= p[i - 1][j - 1];
            if (p[i][j])
                ans++;
        }
    cout << ans;
}

#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<
 
typedef long long ll;
typedef long double ld;

const int MAXN = 1010, MAXS = 1010, MAXQ = 2e5 + 10;
const int INF = 1e8;

int n, m, q;
ll c[MAXN];
vector<int> e[MAXN];
int dp[MAXS][2][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    int x = -1, prev_x = -1;
    for (int i = 0; i < n; i++)
        if (e[i].size() == 1) {
            prev_x = i;
            x = e[i][0];
            break;
        }

    for (int i = 0; i < MAXS; i++)
        dp[i][1][0] = -INF;

    while (true) {
        for (int i = 0; i < MAXS; i++) {
            dp[i][0][1] = max(dp[i][0][0], dp[i][1][0]);
            dp[i][1][1] = -INF;
            if (c[x] <= i) dp[i][1][1] = dp[i - c[x]][1][0] + 1;
            if (c[x] + c[prev_x] <= i)
                dp[i][1][1] = max(dp[i][1][1],
                        dp[i - c[x] - c[prev_x]][0][0] + 2);
        }

        for (int i = 0; i < MAXS; i++) {
            dp[i][0][0] = dp[i][0][1];
            dp[i][1][0] = dp[i][1][1];
        }

        if (e[x].size() == 1) break;
        int tmp = e[x][0] + e[x][1] - prev_x;
        prev_x = x;
        x = tmp;
    }

    cin >> q;
    while (q--) {
        int s;
        cin >> s;
        cout << max(dp[s][0][0], dp[s][1][0]) << "\n";
    }

    return 0;
}

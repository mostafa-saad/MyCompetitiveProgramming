#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<
 
typedef long long ll;
typedef long double ld;

const int MAXN = 1010, MAXQ = 2e5 + 10;
const ll INF = 1e15;

int n, m, q;
ll c[MAXN];
vector<int> e[MAXN];
ll dp[MAXN][2][2];

pair<int, int> query[MAXQ];
int ans[MAXQ];


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

    for (int i = 0; i <= n; i++)
        dp[i][0][0] = dp[i][1][0] = INF;
    dp[0][0][0] = 0;

    while (true) {
        for (int i = 0; i <= n; i++) {
            dp[i][0][1] = min(dp[i][0][0], dp[i][1][0]);
            dp[i][1][1] = INF;
            if (i >= 1) dp[i][1][1] = min(dp[i][1][1],
                    dp[i - 1][1][0] + c[x]);
            if (i >= 2) dp[i][1][1] = min(dp[i][1][1],
                    dp[i - 2][0][0] + c[x] + c[prev_x]);
        }

        for (int i = 0; i <= n; i++) {
            dp[i][0][0] = dp[i][0][1];
            dp[i][1][0] = dp[i][1][1];
        }

        if (e[x].size() == 1) break;
        int tmp = e[x][0] + e[x][1] - prev_x;
        prev_x = x;
        x = tmp;
    }

    for (int i = n; i >= 0; i--) {
        dp[i][0][0] = min(dp[i][0][0], dp[i][1][0]);
        if (i < n) dp[i][0][0] = min(dp[i][0][0], dp[i + 1][0][0]);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> query[i].first;
        query[i].second = i;
    }
    sort(query, query + q);
    int answer = 0;
    for (int i = 0; i < q; i++) {
        while (answer < n && dp[answer + 1][0][0] <= query[i].first)
            answer++;
        ans[query[i].second] = answer;
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << "\n";

    return 0;
}

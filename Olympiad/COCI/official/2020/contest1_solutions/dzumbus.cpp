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
ll dp_in[MAXN][MAXN], dp_out[MAXN][MAXN];
int subtree_size[MAXN];

pair<int, int> query[MAXQ];
int ans[MAXQ];


ll prev_dp_in[MAXN], prev_dp_out[MAXN];

void calc(int i, int parent = -1) {
    subtree_size[i] = 1;
    if (i != n) {
        for (int j : e[i]) {
            if (j != parent) {
                calc(j, i);
                subtree_size[i] += subtree_size[j];
            }
        }
    }

    for (int k = 0; k <= n; k++)
        dp_in[i][k] = dp_out[i][k] = INF;
    dp_out[i][0] = 0;

    int total = 0;
    prev_dp_in[0] = INF;
    prev_dp_out[0] = 0;

    for (int j : e[i]) {
        if (j == parent) continue;

        for (int k = 0; k <= total + subtree_size[j]; k++)
            dp_in[i][k] = dp_out[i][k] = INF;

        for (int a = 0; a <= total; a++) {
            for (int b = 0; b <= subtree_size[j]; b++) {
                dp_out[i][a + b] = min(dp_out[i][a + b],
                        prev_dp_out[a] + min(dp_in[j][b], dp_out[j][b]));

                dp_in[i][a + b] = min(dp_in[i][a + b],
                        min(prev_dp_out[a] + dp_in[j][b],
                            prev_dp_in[a] + min(dp_in[j][b], dp_out[j][b])));
                if (b > 0)
                    dp_in[i][a + b] = min(dp_in[i][a + b],
                            min(prev_dp_out[a], prev_dp_in[a]) + dp_out[j][b - 1] + c[j]);
            }
        }

        total += subtree_size[j];
        for (int k = 0; k <= total; k++) {
            prev_dp_in[k] = dp_in[i][k];
            prev_dp_out[k] = dp_out[i][k];
        }
    }

    for (int k = total; k >= 0; k--)
        dp_in[i][k + 1] = min(INF, dp_in[i][k] + c[i]);
    dp_in[i][0] = INF;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        dp_in[i][0] = -1;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        if (dp_in[i][0] == -1) {
            calc(i);
            e[n].push_back(i);
        }
    }

    c[n] = INF;
    calc(n);
    for (int i = n - 1; i >= 0; i--)
        dp_out[n][i] = min(dp_out[n][i], dp_out[n][i + 1]); 

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> query[i].first;
        query[i].second = i;
    }
    sort(query, query + q);
    int answer = 0;
    for (int i = 0; i < q; i++) {
        while (answer < n && dp_out[n][answer + 1] <= query[i].first)
            answer++;
        ans[query[i].second] = answer;
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << "\n";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
  
const int MAXN = 1e6 + 10;
int n, m;
int match[MAXN], vis[MAXN], tick;
int start[MAXN];
vector<int> e[MAXN];

bool f(int i) {
    if (i == -1) return true;
    if (vis[i] == tick) return false;
    vis[i] = tick;

    for (int j = start[i]; ; j = (j - 1) & i) {
        if (f(match[j])) {
            match[j] = i;
            return true;
        }
        if (j == 0) break;
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        match[i] = -1;

    for (int i = m + n - 1; i >= m; i--) {
        int j = (1 << 20) - 1 - i;
        j = i + (j & -j);
        if (j < m + n) start[i] = start[j];
        else start[i] = n - 1;
        while ((start[i] & i) != start[i]) start[i]--;
    }

    for (int i = m; i < m + n; i++) {
        tick++;
        assert(f(i));
    }

    for (int i = 0; i < n; i++)
        cout << i << " " << match[i] << "\n";

    return 0;
}


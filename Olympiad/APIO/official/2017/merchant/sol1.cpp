#include <bits/stdc++.h>

template<typename T> void domax(T &a, T b) { if (b > a) a = b; }
template<typename T> void domin(T &a, T b) { if (b < a) a = b; }

const long long inf = 3e18, MaxT = 10ll*1000*1000;
const int MaxN = 105, MaxK = 1005;

int n, m, K;
long long b[MaxN][MaxK], s[MaxN][MaxK], dist[MaxN][MaxN], best[MaxN][MaxN], cost[MaxN][MaxN];

bool can(long long eff) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] < inf) {
                assert(dist[i][j] <= 1000ll*1000*1000); // MaxT * MaxN
                assert(eff <= 1000ll*1000*1000 + 1);
                cost[i][j] = dist[i][j] * eff - best[i][j];
                assert(-1000ll*1000*1000 <= cost[i][j]);
                assert(cost[i][j] <= (1000*1000*1000ll + 1) * 1000ll*1000*1000);
            } else {
                cost[i][j] = inf;
            }
        }
    }
    for (int m = 0; m < n; m++) {
        for (int s = 0; s < n; s++) {
            for (int e = 0; e < n; e++) {
                domin(cost[s][e], cost[s][m] + cost[m][e]);
                if (cost[s][e] < -inf) {
                    cost[s][e] = -inf;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (cost[i][j] + cost[j][i] <= 0) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d", &n, &m, &K);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < K; k++) {
            scanf("%lld%lld", b[i]+k, s[i]+k);
            if (b[i][k] == -1) b[i][k] = inf;
            if (s[i][k] == -1) s[i][k] = -inf;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = inf;
        }
    }
    for (int i = 0; i < m; i++) {
        int v, w; long long t;
        scanf("%d%d%lld", &v, &w, &t);
        v--; w--;
        dist[v][w] = t;
        assert(t <= 10ll*1000*1000);
    }

    for (int m = 0; m < n; m++) {
        for (int s = 0; s < n; s++) {
            for (int e = 0; e < n; e++) {
                domin(dist[s][e], dist[s][m] + dist[m][e]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            best[i][j] = 0; // carrying no item
            for (int k = 0; k < K; k++) {
                domax(best[i][j], s[j][k] - b[i][k]);
            }
        }
    }
    
    long long lo = 1ll, hi = 1000ll * 1000 * 1000;
    long long ans = 0ll;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (can(mid)) {
            lo = mid + 1;
            ans = mid;
        } else {
            hi = mid - 1;
        }
    }
    assert(!can(ans+1));

    printf("%lld\n", ans);
}


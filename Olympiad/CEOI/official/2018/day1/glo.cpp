// Patryk Czajka

#include <cstdio>
#include <cassert>

inline int max(int a, int b) {
    return a > b ? a : b;
}

int n, X, res;
const int maxN = 2e5 + 10;

int t[maxN];
int dp[maxN];
int res_part[maxN];
int dp_i;

void reset() {
    dp_i = 0;
}

int add(int x) {
    int a = -1, b = dp_i, avg;
    while(b - a > 1) {
        avg = (a + b) / 2;
        if(dp[avg] < x) a = avg;
        else b = avg;
    }
    dp[b] = x;
    dp_i = max(dp_i, b + 1);
    return b + 1;
}


void check(int i) {
    int a = -1, b = dp_i, avg;
    while(b - a > 1) {
        avg = (a + b) / 2;
        if(dp[avg] < X - t[i]) a = avg;
        else b = avg;
    }
    res = max(res_part[i] + b, res);
}


int main() {
    int ans;
    ans = scanf("%d%d", &n, &X);
    assert(ans >= 0);
    for(int i = 0; i < n; ++i) {
        ans = scanf("%d", t + i);
        assert(ans >= 0);
        res_part[i] = add(t[i]);
    }

    reset();
    for(int i = n - 1; i >= 0; --i) {
        check(i);
        add(-t[i]);
    }
    printf("%d\n", res);
}

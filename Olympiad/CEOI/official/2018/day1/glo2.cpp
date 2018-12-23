// Patryk Czajka
// O(n*logn)

#include <cstdio>


inline int max(int a, int b) {
    return a > b ? a : b;
}

int n, X, res;
const int maxN = 2e5+10;


int dp_max[maxN];
int dp_min[maxN];
int mx_i, mn_i;

int find(int* dp, int i, int val) {
    int a = -1, b = i, avg;
    while(b - a > 1) {
        avg = (a + b) / 2;
        if(dp[avg] < val) a = avg;
        else b = avg;
    }
    return b;
}

int add(int* dp, int &i, int val) {
    int b = find(dp, i, val);
    dp[b] = val;
    i = max(i, b + 1);
    return b;
}

void count(int left) {
    if(left == 0)
        return;

    int val;
    scanf("%d", &val);
    int b_here = add(dp_max, mx_i, val);

    count(left - 1);

    res = max(b_here + find(dp_min, mn_i, -val+X) + 1, res);
    add(dp_min, mn_i, -val);
}


int main() {
    scanf("%d%d", &n, &X);
    count(n);
    printf("%d\n", res);
}

#include <cstdio>
#include <cmath>

#define MAXN 100002

typedef long long llint;

using namespace std;

int N, K, first_key;
int key[MAXN];

llint miss[MAXN];

int main(void) {

    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; ++i) {
        int x; scanf("%d", &x);
        key[--x] = i;
        if (i == 0) first_key = x;
    }

    llint sol = (llint) abs(key[0] - key[first_key]);
    if (key[first_key] > key[0]) sol = N - sol;

    for (int i = 1; i <= N; ++i) {
        int curr = key[i - 1], prev = key[(i - 2 + N) % N];
        int wrong = abs(curr - prev);
        if (prev > curr) wrong = N - wrong;
        miss[i] = miss[i - 1] + (llint) wrong;
    }

    sol += miss[N] * (K/N);
    sol += miss[K%N] - miss[1];
    
    printf("%lld\n", sol);

    return 0;

}

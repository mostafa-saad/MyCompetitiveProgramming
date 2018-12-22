#include <cstdio>

#define MAXN 100010

using namespace std;

typedef long long llint; 

int N, Q;

llint pref_xor[2*MAXN];

int main(void) {

    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        llint x; scanf("%lld", &x);
        pref_xor[i + 1] = pref_xor[i] ^ x;
    }

    for (int i = 0; i <= N; ++i) 
        pref_xor[i + N + 1] = pref_xor[i];

    scanf("%d", &Q);
    for (int i = 0; i < Q; ++i) {
        llint l, r; scanf("%lld%lld", &l, &r); --l; --r;
        r = l % (N + 1) + (r - l + 1) % (N + 1); l %= N + 1; 
        printf("%lld\n", pref_xor[r] ^ pref_xor[l]);
    }

    return 0;

}

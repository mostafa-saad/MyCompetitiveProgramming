#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>

using namespace std;

typedef unsigned uint;
typedef long long Int;

const int INF = 1001001001;
const Int INFLL = 1001001001001001001LL;

template<typename T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template<typename T> void chmin(T& a, T b) { if (a > b) a = b; }
template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }

int rowflip[(1<<21) + 50], colflip[(1<<21) + 50];
int rowall[21], colall[21];

void flip(int *seg, int *all, int dep, int x)
{
    int p = (1<<dep) + x, sz = 1;
    seg[p] ^= 1; p >>= 1; sz <<= 1; --dep;

    while (p > 0) {
        if (seg[p] % sz == 0) {
            --all[dep];
        }
        seg[p] = seg[2*p] + seg[2*p+1];
        if (seg[p] % sz == 0) {
            ++all[dep];
        }
        p >>= 1; sz <<= 1; --dep;
    }
}

int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);

    for (int i = 0; i <= N; ++i) {
        rowall[i] = 1 << i;
        colall[i] = 1 << i;
    }

    for (int i = 0; i < Q; ++i) {
        int T, X;
        scanf("%d%d", &T, &X);

        --X;

        if (T == 0) {
            flip(rowflip, rowall, N, X);
        } else {
            flip(colflip, colall, N, X);
        }

        Int leaves = (1LL << N) * (1LL << N);

        for (int j = 0; j < N; ++j) {
            leaves -= (Int)rowall[j] * colall[j] * 3;
        }

        printf("%lld\n", 4 * (leaves - 1) / 3 + 1);
    }

    return 0;
}

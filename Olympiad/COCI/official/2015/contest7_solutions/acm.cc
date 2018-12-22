#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[3][150 * 1000];
int memo[150 * 1001][3]; 
int n;
int prvi, drugi, treci;
int sljedeci[3];
const int INF = 1000 * 1000 * 1000;

int dp(int k, int koji) {
    int &ref = memo[k][koji];
    if (ref != -1) return ref;
    if (k == n)
        return ref = (koji == treci ? 0 : INF);
    ref = a[koji][k] + dp(k + 1, koji);
    if (koji != treci)
        ref = min(ref, a[sljedeci[koji]][k] + dp(k + 1, sljedeci[koji]));
    return ref;
}

int solve(int p, int q, int r) {
    prvi = p;
    drugi = q;
    treci = r;
    sljedeci[prvi] = drugi;
    sljedeci[drugi] = treci;
    memset(memo, -1, sizeof(memo));
    return a[prvi][0] + dp(1, prvi);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &a[i][j]);
    printf("%d\n", min(min(min(min(min( 
                solve(0, 1, 2),
                solve(0, 2, 1)),
                solve(1, 0, 2)),
                solve(1, 2, 0)),
                solve(2, 0, 1)),
                solve(2, 1, 0)));
}

#include <cstdio>
#include <algorithm>
using namespace std;

const int MM = 101;
const int KK = 505;
int ukupno[MM];
long long dp[MM][KK];

inline long long zbroj_prvih(int n) {
    return (long long)n * (n + 1) / 2;
}

inline long long rijesi_zgradu(int n, int k) {
    int komada = k + 1;
    int manji_komad = n / komada;
    int veci_komad = (n + komada - 1) / komada;
    int br_vecih = n % komada;
    int br_manjih = komada - br_vecih;
    return br_manjih * zbroj_prvih(manji_komad) +
        br_vecih * zbroj_prvih(veci_komad);
}

int main() {
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    while (N--) {
        int zgrada;
        scanf("%d", &zgrada);
        ++ukupno[zgrada];
    }
    for (int m = 1; m <= M; ++m)
        for (int k = 0; k <= K; ++k) {
            dp[m][k] = rijesi_zgradu(ukupno[m], 0) + dp[m - 1][k];
            for (int i = 1; i <= k; ++i)
                dp[m][k] = min(dp[m][k],
                        rijesi_zgradu(ukupno[m], i) + dp[m - 1][k - i]);
            }
    printf("%lld\n", dp[M][K]);
}

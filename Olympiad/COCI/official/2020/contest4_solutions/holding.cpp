#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 5;
const int maxk = 10000/4 + 5;
int N, K;
int L, R;
int a[maxn];
int suma;
int sol;
int dp[maxn][maxn][maxk];
int solL[maxn][maxk];

int main()
{
    cin >> N >> L >> R >> K;
    K = min(K, N * N / 4 + 2);
    for (int i = 1; i <= N; i++)
        cin >> a[i];
    for (int i = L; i <= R; i++)
        suma += a[i];
    for (int i = L; i <= R; i++)
    {
        for (int j = L - 1; j > 0; j--)
        {
            for (int k = 0; k <= K; k++)
            {
                dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
                dp[i][j][k] = max(dp[i][j][k], dp[i][j + 1][k]);
                int cijena  = i - j;
                if (k >= cijena) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j + 1][k - cijena] + a[i] - a[j]);
            }
        }
    }

    for (int i = L - 1; i <= R; i++)
        for (int j = 0; j <= K; j++)
            solL[i][j] = dp[i][1][j];

    memset(dp, 0, sizeof dp);

    for (int i = R; i >= L; i--)
    {
        for (int j = R + 1; j <= N; j++)
        {
            for (int k = 0; k <= K; k++)
            {
                dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j][k]);
                dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k]);
                int cijena = j - i;
                if (k >= cijena) dp[i][j][k] = max(dp[i][j][k], dp[i + 1][j - 1][k - cijena] + a[i] - a[j]);
            }
        }
    }

    for (int i = L - 1; i <= R; i++)
        for (int j = 0; j <= K; j++)
            sol = max(sol, solL[i][j] + dp[i + 1][N][K - j]);

    cout << suma - sol << '\n';
}

/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Bartosz Kostka                                *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAXN = 1007;
const long long INF = 2000000000000000007LL;

static int tab[MAXN], n, s;
static long long dp[MAXN][MAXN];

static long long min(long long a, long long b)
{
    if(a<b)
        return a;
    return b;
}

static long long max(long long a, long long b)
{
    if(a>b)
        return a;
    return b;
}

//dp[i][j] - i pociągow było w B, j pociągów w A

int main()
{
    scanf("%d%d", &n, &s);
    for(int i=1; i<=n; i++)
        scanf("%d", &tab[i]);
    for(int i=2; i<=n; i++)
        if(tab[i-1]>=tab[i])
            tab[i] = tab[i-1]+1;
    for(int i=1; i<=n; i++)
        dp[i][0] = tab[i]+s;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++)
        {
            dp[i][j] = INF;
            for(int k=1; i-k>=j; k++)
                dp[i][j] = min(dp[i][j], max(dp[i-k][j] + s + k - 1, dp[i][0]));
            for(int k=1; k<=j; k++)
                dp[i][j] = min(dp[i][j], dp[i][j-k] + s + k - 1);
        }
    printf("%lld\n", dp[n][n]);
    return 0;
}

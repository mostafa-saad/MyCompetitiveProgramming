/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Bartosz Kostka                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAXN = 1000007;
const long long INF = 4000000007LL;

static long long tab[MAXN];
static long long dp[MAXN];

long long min(long long a, long long b)
{
    if(a<b)
        return a;
    return b;
}

long long max(long long a, long long b)
{
    if(a>b)
        return a;
    return b;
}

int main()
{
    int n, s;
    scanf("%d%d", &n, &s);
    for(int i=1; i<=n; i++)
        scanf("%lld", &tab[i]);

    //pociagi nie mogą wyruszac w tym samym czasie
    for(int i=2; i<=n; i++)
        if(tab[i-1]>=tab[i])
            tab[i] = tab[i-1]+1;

    int lk = 0;
    for(int i=1; i<=n; i++)
    {
        dp[i] = INF;
        int ilepociagow = i-lk-1;
        while(lk < i && max(dp[lk]+ilepociagow, tab[i]) + ilepociagow + 2*s < dp[i])
        {
            dp[i] = max(dp[lk]+ilepociagow, tab[i]) + ilepociagow + 2*s;
            lk++;
            ilepociagow--;
        }
        lk--;
    }
    //for(int i=1; i<n; i++)
    //printf("%lld ", dp[i]);
    printf("%lld\n", dp[n]);
    return 0;
}

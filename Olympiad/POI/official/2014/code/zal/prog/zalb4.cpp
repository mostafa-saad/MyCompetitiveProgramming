/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Bartosz Kostka                                *
 *   Zlozonosc czasowa:    O(400n)                                       *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Heurystyka bedaca modyfikacja rozwiazania     *
 *                         kwadratowego.                                 *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAXN = 1000007;
const long long INF = 2000000000000000007LL;

static int tab[MAXN];
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
        scanf("%d", &tab[i]);

    //pociagi nie mogą wyruszac w tym samym czasie
    for(int i=2; i<=n; i++)
        if(tab[i-1]>=tab[i])
            tab[i] = tab[i-1]+1;

    for(int i=1; i<=n; i++)
    {
        dp[i] = INF;
        for(int k=max(0,i-400); k<i; k++)
        {
            int ilepociagow = i-k-1;
            dp[i] = min(dp[i], max(dp[k]+ilepociagow, tab[i]) + ilepociagow + 2*s);
        }
    }
    //for(int i=1; i<n; i++)
    //printf("%lld ", dp[i]);
    printf("%lld\n", dp[n]);
    return 0;
}

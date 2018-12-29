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

const unsigned int MAXN = 1000007;
const unsigned int INF = -1;

static unsigned int tab[MAXN];
static unsigned int dp[MAXN];

unsigned int min(unsigned int a, unsigned int b)
{
    if(a<b)
        return a;
    return b;
}

unsigned int max(unsigned int a, unsigned int b)
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
        scanf("%u", &tab[i]);

    //pociagi nie mogą wyruszac w tym samym czasie
    for(int i=2; i<=n; i++)
        if(tab[i-1]>=tab[i])
            tab[i] = tab[i-1]+1;

    int lk = 0;
    for(int i=1; i<=n; i++)
    {
        dp[i] = INF;
        int ilepociagow = i-lk-1;
        while(lk < i && (long long)(max(dp[lk]+ilepociagow, tab[i]) + 1LL*ilepociagow + 2LL*s) < dp[i])
        {
            dp[i] = max(dp[lk]+ilepociagow, tab[i]) + ilepociagow + 2LL*s;
            lk++;
            ilepociagow--;
        }
        lk--;
    }
    printf("%u\n", dp[n]);
    return 0;
}

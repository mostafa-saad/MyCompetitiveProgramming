/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Zaladunek                                     *
 *   Autor:                Bartosz Kostka                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Nie uzywa liczb 64-bitowych.                  *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAXN = 1000007;
const int INF = 2000000007;

static int tab[MAXN];
static int dp[MAXN];

int min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

int max(int a, int b)
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
    printf("%d\n", dp[n]);
    return 0;
}

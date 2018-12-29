/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Czarnoksieznicy okraglego stolu                    *
 *   Autor programu:       Bartek Kostka                                      *
 *   Zlozonosc czasowa:    O(n * n!)                                          *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         troche sprytniejsze rozwiazanie wykladnicze        *
 *****************************************************************************/


#include "bits/stdc++.h"

using namespace std;

const int MAXN = 1000007;
const int MAXK = 1007;

int n, k, p;
int tab[MAXN];
int used[MAXN];
bool enemy[1007][1007];

long long go(int a)
{
    if(a==n)
    {
        if((enemy[tab[n-1]][tab[0]]==0) && (abs(tab[n-1]-tab[0]) <= p))
        {
            for(int i=0; i<n; i++)
                cerr << tab[i] << " ";
            cerr << "\n";
            return 1;
        }
        else
            return 0;
    }
    int pre = tab[a-1];
    long long wyn = 0;
    for(int i=-p; i<=p; i++)
    {
        int cur = pre+i;
        if(cur < 1 || cur > n)
            continue;
        if(enemy[pre][cur])
            continue;
        if(used[cur]==0)
        {
            used[cur] = 1;
            tab[a] = cur;
            wyn += go(a+1);
            used[cur] = 0;
        }
    }
    return wyn;
}

int main()
{
    scanf("%d%d%d", &n, &k, &p);
    while(k--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        enemy[a][b] = true;
    }
    tab[0] = n;
    used[n] = 1;
    printf("%lld\n", go(1));
    return 0;
}

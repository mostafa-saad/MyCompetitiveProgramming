/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Szymon Stankiewicz                            *
 *   Zlozonosc czasowa:    O(n!)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAX_N=1000007;

int K,p,q, tab[MAX_N], N, out[MAX_N];

bool gen(int pop, int nr)
{
    out[nr]=pop;
    if(nr==0)
    {
        tab[p]--;
        return gen(p, 1);
    }
    if(nr==N && pop==q)
        return true;
    if(nr>N)
        return false;
    for(int i = 1; i<=K; i++)
        if(tab[i]>0 && i!=pop)
        {
            tab[i]--;
            if(gen(i, nr+1))
                return true;
            tab[i]++;
        }
    return false;
}

int main()
{
    scanf("%d %d %d", &K, &p, &q);
    for(int i = 1; i<=K; i++)
    {
        scanf("%d", tab+i);
        N+=tab[i];
    }
    if(gen(0, 0))
        for(int i = 1; i<=N; i++)
            printf("%d ", out[i]);
    else
        printf("0\n");
    return 0;
}

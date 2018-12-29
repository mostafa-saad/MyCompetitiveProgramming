/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wiedzmak (WIE)                                            *
 *   Plik:     wies2.cpp                                                 *
 *   Autor:    Tomasz Kulczynskii                                        *
 *   Opis:     Rozwiazanie bez kolejki priorytetowej O(n^2*4^p*2^p)      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

const int N = 213;

int miecz[N];           // maska dostepnych mieczy
vector<int> kraw[N],koszt[N],pot[N]; // krawedzie grafu
int n, m, p, k;
int wyn[N * (1<<13)]; // wyniki dla wierzcholkow z maskami mieczy

int main()
{
    scanf("%d %d %d %d", &n, &m, &p, &k);
    for(int i = 0; i < k; i++)
    {
        int w,q;
        scanf("%d %d", &w, &q);
        for(int j = 0; j < q; j++)
        {
            int x;
            scanf("%d", &x);
            miecz[w] |= 1<<(x-1);
        }
    }
    for(int i = 0; i < m; i++)
    {
        int v, w, t, s, potw = 0;
        scanf("%d %d %d %d", &v, &w, &t, &s);
        for(int j = 0; j < s; j++)
        {
            int x;
            scanf("%d", &x);
            potw |= 1<<(x-1);
        }

        kraw[v].push_back(w);
        koszt[v].push_back(t);
        pot[v].push_back(potw);
        
        kraw[w].push_back(v);
        koszt[w].push_back(t);
        pot[w].push_back(potw);
    }

    for(int i = 0; i < N*(1<<13); i++)
        wyn[i] = 1<<30;

    wyn[ miecz[1] * N + 1 ] = 0;

    while(1)
    {
        int a = 0;
        while(a < N*(1<<p) && wyn[a] < 0) 
            a++;
        for(int i = a+1; i < N*(1<<p); i++)
            if(wyn[i] >= 0 && wyn[i] < wyn[a])
                a = i;
        if(a == N*(1<<p) || wyn[a]==(1<<30)) 
            break;
        if(a % N == n)
        {
            printf("%d\n",wyn[a]);
            return 0;
        }

        int mie = a/N;
        int g = a%N;

        for(int i = 0; i < (int)kraw[g].size(); i++)
        {
            int cel = (mie | miecz[kraw[g][i]]) * N + kraw[g][i];
            if((mie | pot[g][i]) == mie  &&  wyn[a] + koszt[g][i] < wyn[cel])
                wyn[cel] = wyn[a] + koszt[g][i];
        }

        wyn[a] = -1;
    }
    puts("-1");
    return 0;
}

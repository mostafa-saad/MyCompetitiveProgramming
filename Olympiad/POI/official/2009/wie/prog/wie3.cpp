/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wiedzmak (WIE)                                            *
 *   Plik:     wie3.cpp                                                  *
 *   Autor:    Tomasz Kulczynskii                                        *
 *   Opis:     Rozwiazanie podobne do wzorcowego O((n+m)*2^p*log(~))     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int N = 213;
const int inf = 1<<30;

int miecz[N];           // maska dostepnych mieczy
vector<int> kraw[N],koszt[N],pot[N]; // krawedzie grafu
int n, m, p, k;
int wyn[N * (1<<13)]; // wyniki dla wierzcholkow z maskami mieczy
set<pair<int,int> > kol;

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
        wyn[i] = inf;

    wyn[ miecz[1] * N + 1 ] = 0;
    kol.insert(make_pair(0, miecz[1] * N + 1));

    while(!kol.empty())
    {
        int a = kol.begin() -> second;
        kol.erase(kol.begin());
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
            {
                if(wyn[cel] < inf) 
                    kol.erase(make_pair(wyn[cel],cel));
                wyn[cel] = wyn[a] + koszt[g][i];
                kol.insert(make_pair(wyn[cel],cel));
            }
        }

        wyn[a] = -1;
    }
    puts("-1");
    return 0;
}

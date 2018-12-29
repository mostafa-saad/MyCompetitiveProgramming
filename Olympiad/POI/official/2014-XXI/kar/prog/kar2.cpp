/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m log n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         W wezlach drzewa trzymane mozliwe pary        *
 *                         (poczatek,koniec) zamiast macierzy            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int,int> PI;

const int infty = (int)1e9+1;
const int maxn = 200*1000;

vector<PI> C[4*maxn+3];
PI P[2*maxn+1];


void merge(vector<PI> &a, vector<PI> &b, vector<PI> &c)
{
    c.clear();
    for(int i=0; i<(int)a.size(); i++)
        for(int j=0; j<(int)b.size(); j++)
            if (a[i].second<=b[j].first)
                c.push_back(PI(a[i].first,b[j].second));
    if (c.empty())
        return;
    sort(c.begin(),c.end());
    c.erase(unique(c.begin(),c.end()),c.end());
}

int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d %d",&P[i].first,&P[i].second);
    int K = 1;
    while(K<n)
        K*=2;
    for(int i=n; i<K; i++)
        P[i].first = P[i].second = infty;
    for(int i=0; i<K; i++)
    {
        C[K+i].push_back(PI(P[i].first,P[i].first));
        if (P[i].first!=P[i].second)
            C[K+i].push_back(PI(P[i].second,P[i].second));
    }
    for(int i=K-1; i>=1; i--)
        merge(C[2*i],C[2*i+1],C[i]);
    scanf("%d",&m);
    for(int i=0; i<m; i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        swap(P[x],P[y]);
        swap(C[K+x],C[K+y]);
        int t;
        t = (K+x)/2;
        while(t>0)
        {
            merge(C[2*t],C[2*t+1],C[t]);
            t = t/2;
        }
        t = (K+y)/2;
        while(t>0)
        {
            merge(C[2*t],C[2*t+1],C[t]);
            t = t/2;
        }
        printf(C[1].empty() ? "NIE\n" : "TAK\n");
    }
    return 0;
}

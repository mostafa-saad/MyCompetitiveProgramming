/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O((n+g) log g)                                *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Prawy koniec przedzialu wlicza do wyniku      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N= 1000000;
const int G= 1000000;
const int MAX = 1000000002;

vector<int> V[N];

int rozmiar[G],g;

int bin_search(int x)// znajdz pierwsza pozycje >=x
{
    if(rozmiar[0]>=x) return 0;
    int p=0,k=g;
    while(p+1<k)
    {
        int m=(p+k)/2;
        if(rozmiar[m]<x) p=m;
        else k=m;
    }
    return k;
}

int mrowa,mrowb;//krawedz przy ktorej jest mrowkojad
int k;
int ojc[N];//numer ojca w drzewie
int prz[N][2]; //przedzial, w jakim musialaby sie znalezc grupa, zeby doszla do mrowkojada

void dfs(int u)
{
    //   printf("%d: %d %d\n",u+1,prz[u][0],prz[u][1]);
    for(int i=0; i<(int)V[u].size(); ++i)
    {
        int t=V[u][i];
        if(t==ojc[u]) continue;
        int e=V[t].size();
        if(e>1) --e;
        for(int j=0; j<2; ++j)
        {
            long long q=1LL*prz[u][j]*e;
            if(q>MAX) q=MAX+1;
            prz[t][j]=q;
        }
        ojc[t]=u;
        dfs(t);
    }
}

int main()
{
    int n;
    scanf("%d%d%d",&n,&g,&k);
    for(int i=0; i<n; ++i) V[i].clear();
    for(int i=0; i<g; ++i) scanf("%d",&rozmiar[i]);
    for(int i=0; i<n-1; ++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        --a;
        --b;
        if(i==0)
        {
            mrowa=a;
            mrowb=b;
        }
        V[a].push_back(b);
        V[b].push_back(a);
    }
    for(int i=0; i<2; ++i)
    {
        ojc[mrowa]=mrowb;
        prz[mrowa][0]=k;
        prz[mrowa][1]=k+1;
        dfs(mrowa);
        swap(mrowa,mrowb);
        //zrob to samo po drugiej stronie mrowkojada
    }
    sort(rozmiar,rozmiar+g);
    long long ile=0;
    for(int i=0; i<n; ++i) if(V[i].size()==1)
        {
            ile+=bin_search(prz[i][1]+1)-bin_search(prz[i][0]);
        }
    printf("%lld\n",ile*k);
}

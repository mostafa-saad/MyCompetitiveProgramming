/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(n^2 * g)                                    *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Symulujemy ruch kazdej grupy mrowek           *
 *                         z kazdego liscia.                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int N= 1000000;
const int G= 1000000;

vector<int> V[N];

int rozmiar[G];
int mrowa,mrowb;//krawedz przy ktorej jest mrowkojad
int k;

//wierzcholek, skad przyszedlem, ile jest mrowek
bool dfs(int u, int pr, int x)
{
    int dziel=V[u].size();
    if(pr!=-1) dziel--;
    if(dziel==0) return 0;
    x/=dziel;
    if(x==0) return 0;
    for(int i=0; i<(int)V[u].size(); ++i)
        if(V[u][i]!=pr)
        {
            int t=V[u][i];
            if((u==mrowa && t==mrowb) || (u==mrowb && t==mrowa))
            {
                if(x==k) return 1;
                else return 0;
            }
            if(dfs(t,u,x)) return 1;
        }
    return 0;
}

int main()
{
    int n,g;
    scanf("%d%d%d",&n,&g,&k);
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
    long long ile=0;
    for(int i=0; i<n; ++i)
        if(V[i].size()==1)
            for(int j=0; j<g; ++j)
                if(dfs(i,-1,rozmiar[j])) ++ile;
    printf("%lld\n",ile*k);
}

/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(ng log m)   m - rozmiar najwiekszej z grup  *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Kompresujemy drzewo tak, aby nie bylo         *
 *                         wierzcholkow o stopniu 2 (poza dwoma          *
 *                         wyroznionymi). W kazdym kroku teraz grupa     *
 *                         bedzie zmniejszac sie przynajmniej dwukrotnie.*
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
int kier[N];
bool start;
//wierzcholek, skad przyszedlem, ile jest mrowek
bool dfs(int u, int x)
{
    int dziel=V[u].size();
    if(!start) dziel--;
    start=0;
    if(dziel==0) return 0;
    x/=dziel;
    if(x==0) return 0;
    int t=kier[u];
    if((u==mrowa && t==mrowb)|| (u==mrowb && t==mrowa)) //krawedz z mrowkojadem
    {
        if(x==k) return 1;
        else return 0;
    }
    if(dfs(t,x)) return 1;
    return 0;
}

void dfs_pocz(int u)
{
    for(int i=0; i<(int)V[u].size(); ++i)
    {
        int t=V[u][i];
        if(kier[t]==-1)
        {
            kier[t]=u;
            dfs_pocz(t);
        }
    }
}

int przejdz(int u,int sk)
{
    while(V[u].size()==2 && u!=mrowa && u!=mrowb)
    {
        int e=-1;
        for(int i=0; i<(int)V[u].size(); ++i) if(V[u][i]!=sk) e=V[u][i];
        sk=u;
        u=e;
    }
    return u;
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
    for(int i=0; i<n; ++i) if(V[i].size()!=2) for(int j=0; j<(int)V[i].size(); ++j) if(V[V[i][j]].size()==2)
                {
                    int e=przejdz(V[i][j],i);
                    V[i][j]=e;
                }
    for(int i=0; i<n; ++i) kier[i]=-1;
    kier[mrowa]=mrowb;
    kier[mrowb]=mrowa;
    dfs_pocz(mrowa);
    dfs_pocz(mrowb);

    long long ile=0;
    for(int i=0; i<n; ++i)
        if(V[i].size()==1)
            for(int j=0; j<g; ++j)
            {
                start=1;
                if(dfs(i,rozmiar[j])) ++ile;
            }
    printf("%lld\n",ile*k);
}

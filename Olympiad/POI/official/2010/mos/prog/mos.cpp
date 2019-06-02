/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 mos.cpp                                       *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O((n + m) * m * log MAX_WIATR)                *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <list>

#include <algorithm>
using namespace std;

const int M = 2001;
const int N = 1001;
const int MAX_WIATR = 1000;

int n,m;
int a[M],b[M],l[M],p[M],stopien[N];
bool bylem[N+M];

struct kraw
{
    int x,r,c;
};

vector<kraw> v[N+M];

bool sciezka(int x,int kon) //znajduje jedna sciezke powiekszajaca przeplyw
{                           //i powieksza wzdluz niej
    if(x==kon) return 1;
    if(bylem[x]) return 0;
    bylem[x]=1;
    for(int i=0;i<(int)(v[x].size());i++) 
    {
        int y=v[x][i].x;
        if(v[x][i].c && sciezka(y,kon)) 
        {
            v[x][i].c--;
            v[y][v[x][i].r].c++;
            return 1;
        }
    }
    return 0;
}

int maxflow(int pocz,int kon)
{
    int flow=0;
    while(1)
    {
        for(int i=0;i<=n+m+1;i++) bylem[i]=0;
        if(!sciezka(pocz,kon)) break;
        flow++;
    }
    return flow;
}

void add_edge( int a, int b, int p ) //dodaje krawedz z a do b o przepustowosci p
{
    kraw k;
    k.x=b;
    k.r=v[b].size();
    k.c=p;
    v[a].push_back(k);

    k.x=a;
    k.r=v[a].size()-1;
    k.c=0;
    v[b].push_back(k);
}

void tworz(int x) //stworzenie grafu dwudzielnego, w ktorym i (1<=i<=n)
                  // jest polaczone z n+j (1<=j<=m), gdy z wierzcholka
                  // i wejsciowego grafu mozna wyjsc krawedzia j
                  // nie przekraczajac kosztu x
                  // 0 jest super-zrodlem a n+m+1 super-ujsciem
{
    for(int i=0;i<=n+m+1;i++) 
        v[i].clear();
    for(int i=1;i<=n;i++) 
        add_edge( 0, i, stopien[i]/2 );
    for(int i=1;i<=m;i++)
    {
        if(l[i]<=x) 
            add_edge( a[i] , n+i, 1 );
        if(p[i]<=x)
            add_edge( b[i] , n+i, 1 );
        add_edge( n+i, n+m+1, 1 );
    }
}

vector<int> kr[N];

void euler() //znajduje i wypisuje cykl eulera w grafie ktory jest
{            //zapisany w listach krawedzi z kazdego wierzcholka kr[]
    if(kr[1].empty()) return;
    int g=1;
    list<int> l;
    list<int>::iterator p,q;
            
    int u=1,e;
    while(!kr[u].empty())
    {
        l.push_back(e=kr[u].back());
        kr[u].pop_back();
        u=a[e]+b[e]-u;
    }

    p=l.begin();
    while(p!=l.end())
    {
        q=p;
        q--;
        if(!kr[g].empty())
        {
            int u=g,e;
            while(!kr[u].empty())
            {
                l.insert(p,e=kr[u].back());
                kr[u].pop_back();
                u=a[e]+b[e]-u;
            }
        }
        p=q;
        p++;
        g=a[*p]+b[*p]-g;
        p++;
    }
    for(p=l.begin();p!=l.end();++p) printf("%d ",*p);
    printf("\n");
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++) 
    {
        scanf("%d %d %d %d",&a[i],&b[i],&l[i],&p[i]);
        stopien[a[i]]++;
        stopien[b[i]]++;
    }
    int L=1,P=MAX_WIATR+1,S;
    while(L<P)  //wyszukiwanie binarne wyniku
    {
        S=(L+P)/2;
        tworz(S);
        if(maxflow(0,n+m+1)==m) P=S;
        else L=S+1;
    }
    if(L>MAX_WIATR) printf("NIE\n");
    else
    {
        printf("%d\n",L);
        tworz(L);
        maxflow(0,n+m+1);
        for(int i=1;i<=m;i++)
            for(int j=0;j<(int)(v[n+i].size());j++)
                if(v[n+i][j].c) kr[v[n+i][j].x].push_back(i);
/*** MiMi:: chyba to jest niepotrzebne
        vector<int> kl;
        for(int i=1;i<=n;i++) for(int j=0;j<(int)(kr[i].size());j++) kl.push_back(kr[i][j]);
        sort(kl.begin(),kl.end());
        for(int i=0;i<(int)(kl.size());i++) if(kl[i]!=i+1) printf("a%d\n",i);
*/
        euler();
    }
    return 0;
}

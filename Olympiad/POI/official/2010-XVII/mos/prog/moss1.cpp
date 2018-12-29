/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 moss1.cpp                                     *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie powolne.                          *
 *   Zlozonosc czasowa:    O(m^3 * log MAX_WIATR)                        *
 *   Zlozonosc pamieciowa: O(m^2)                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <list>
using namespace std;

const int M = 2001;
const int N = 1001;
const int MAX_WIATR = 1000;

int n,m;
int a[M],b[M],l[M],p[M],stopien[N],koniec[N];

vector<int> t[M];

bool c[2*M];
int skoj[2*M];

bool dfs(int v)
{
  c[v]=1;
  for(int i=0;i<(int)(t[v].size());i++)
    if (skoj[t[v][i]]==-1 || (!c[skoj[t[v][i]]] && dfs(skoj[t[v][i]])))
    {
      skoj[v]=t[v][i]; skoj[t[v][i]]=v;
      return 1;
    }
  return 0;
}

int skojarzenie()
{
  for(int i=0;i<m+m;i++) skoj[i]=-1;
  bool d=1;
  while (d)
  {
    d=0;
    for(int i=0;i<m;i++) 
        c[i]=0;
    for(int i=0;i<m;i++) 
        if(skoj[i]==-1 && !c[i]) 
            d|=dfs(i);
  }
  int x=0;
  for(int i=0;i<m;i++) 
      if(skoj[i]!=-1) 
          x++;
  return x;
}

int licznik=0;

void add_edge( int a, int b ) //dodaje krawedz z a do b
{
    licznik++;
    t[a].push_back(b);
}

void tworz(int x) //stworzenie grafu dwudzielnego, w ktorym i (1<=i<=m)
                  // jest polaczone z m+j (1<=j<=m), gdy z wierzcholka,
                  // ktorego jedna z kopii jest i, 
                  // wejsciowego grafu mozna wyjsc krawedzia j
                  // nie przekraczajac kosztu x
{
    licznik=0;
    for(int i=0;i<m+m;i++) 
        t[i].clear();
    koniec[0]=0;
    for(int i=1;i<=n;i++) 
        koniec[i]=koniec[i-1]+stopien[i]/2;
    for(int i=1;i<=m;i++)
    {
        if(l[i]<=x) 
            for(int j=koniec[a[i]-1];j<koniec[a[i]];j++)
                add_edge( j , m+i-1 );
        if(p[i]<=x)
            for(int j=koniec[b[i]-1];j<koniec[b[i]];j++)
                add_edge( j , m+i-1 );
    }
    //fprintf(stderr,"%d %d\n",2*m,licznik);
}

vector<int> kr[N];

void euler() //znajduje i wypisuje cykl eulera w grafie ktory jest
{            //zapisany w listach krawedzi z kazdego wierzcholka kr[]
    if(kr[1].empty()) return;
    int g=1;
    list<int> l;
    list<int>::iterator p;
            
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
        if(skojarzenie()==m) P=S;
        else L=S+1;
    }
    if(L>MAX_WIATR) printf("NIE\n");
    else
    {
        printf("%d\n",L);
        tworz(L);
        skojarzenie();
        int k=0;
        for(int i=0;i<m;i++)
        {
            if(i==koniec[k]) k++;
            kr[ k ].push_back( skoj[i]-m+1 );
        }
        euler();
    }
    return 0;
}

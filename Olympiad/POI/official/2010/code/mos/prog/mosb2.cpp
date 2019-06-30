/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 mosb2.cpp                                     *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie niepoprawne.                      *
 *                         Zwraca dowolny cykl Eulera.                   *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
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
int a[M],b[M],l[M],p[M],stopien[N];
bool bylem[M];

vector<int> kr[N];

list<int> euler() //znajduje i wypisuje cykl eulera w grafie ktory jest
{            //zapisany w listach krawedzi z kazdego wierzcholka kr[]
    if(kr[1].empty()) return list<int>();
    int g=1;
    list<int> l;
    list<int>::iterator p;
            
    int u=1,e;
    while(!kr[u].empty())
    {
        if(bylem[kr[u].back()])
        {
            kr[u].pop_back();
            continue;
        }
        l.push_back(e=kr[u].back());
        kr[u].pop_back();
        bylem[e]=1;
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
                if(bylem[kr[u].back()])
                {
                    kr[u].pop_back();
                    continue;
                }
                l.insert(p,e=kr[u].back());
                kr[u].pop_back();
                bylem[e]=1;
                u=a[e]+b[e]-u;
            }
        }
        g=a[*p]+b[*p]-g;
        p++;
    }
    return l;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++) 
    {
        scanf("%d %d %d %d",&a[i],&b[i],&l[i],&p[i]);
        stopien[a[i]]++;
        stopien[b[i]]++;
        kr[a[i]].push_back(i);
        kr[b[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) if(stopien[i]%2)
    {
        printf("NIE\n");
        return 0;
    }
    list<int> e=euler();
    int L=0,g=1;
    for(list<int>::iterator i=e.begin();i!=e.end();++i) 
    {
        L=max( L, g==a[*i] ? l[*i] : p[*i] );
        g=a[*i]+b[*i]-g;
    }
    printf("%d\n",L);
    for(list<int>::iterator i=e.begin();i!=e.end();++i) 
        printf("%d ",*i);
    printf("\n");
    return 0;
}

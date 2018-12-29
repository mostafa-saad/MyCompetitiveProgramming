/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 moss2.cpp                                     *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie powolne.                          *
 *   Zlozonosc czasowa:    O(2^m * m)                                    *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <list>
using namespace std;

const int M = 2001;
const int N = 1001;

int n,m;
int a[M],b[M],l[M],p[M],stopien[N],x[M];

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
    int ret=1<<30,rozw=0;
    if(m>30) while(1);
    for(int maska=0;maska<(1<<m);maska++)
    {
        int w=0;
        for(int i=1;i<=n;i++) 
            x[i]=0;
        for(int i=1;i<=m;i++)
            if(maska&(1<<(i-1))) 
            {
                w=max(w,l[i]);
                x[a[i]]++;
            }
            else
            {
                w=max(w,p[i]);
                x[b[i]]++;
            }
        int ok=1;
        for(int i=1;i<=n;i++) 
            if(x[i]!=stopien[i]/2)
                ok=0;
        if(ok && ret>w)
        {
            ret=w;
            rozw=maska;
        }
    }
    if(ret==(1<<30))
    {
        printf("NIE\n");
        return 0;
    }
    printf("%d\n",ret);
    for(int i=1;i<=m;i++)
        if(rozw&(1<<(i-1)))
            kr[a[i]].push_back(i);
        else 
            kr[b[i]].push_back(i);
    euler();
    return 0;
}

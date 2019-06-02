/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pows2.cpp                                                  *}
{*   Autor:   Marek Zylak                                                *}
{*   Opis:    Rozwiazanie wolne, z kolejka priorytetowa zgodne z idea    *}
{*            opisana przez autora zadania                               *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <complex>
#include <set>

using namespace std;

#define REP(i,n) for (int _tmp_##i=(int)(n),i=0;i<_tmp_##i;i++)
#define FOR(i,a,b) for (int _tmp_##i=(int)(b),i=(a);i<=_tmp_##i;i++)
#define FORD(i,a,b) for (int _tmp_##i=(int)(b),i=(a);i>=_tmp_##i;i--)

typedef pair<int,int> P;

#define MAXW 1000
#define MAXA 1000

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };


int main()
{
        int w,h;
        assert(scanf("%d%d",&h,&w) == 2);

        assert(w>=1 && w<=MAXW);
        assert(h>=1 && h<=MAXW);

        int n = w * h;
        int *a = new int[n];
        int *c = new int[n];

        REP(j,h) REP(i,w) {
                int x=j*w+i;
                assert(scanf("%d",&a[x]) == 1);
                assert(a[x]!=0 && a[x]>=-MAXA && a[x]<=MAXA);
                c[x]=(a[x]>0);
                a[x]=max(a[x],-a[x]);
        }

        int inf=0;
        REP(i,n) inf=max(inf,a[i]+1);

        int *f = new int[n];
        REP(i,n) f[i]=inf;

        int *head = new int[inf];
        FOR(i,1,inf-1) head[i]=-1;

        int *next=new int[n];

        REP(i,n) if (c[i]) {
                next[i]=head[a[i]];
                head[a[i]]=i;
        }

        set<P> q;

        int ans=0;
        FOR(k,1,inf-1) while (head[k]>=0) {
                int x=head[k];
                head[k]=next[x];

                if (f[x]>a[x]) {
                        f[x]=a[x];
                        ans++;
                        q.insert(P(f[x],x));
                        while (!q.empty()) {
                                int u=(q.begin())->second;
                                q.erase(q.begin());
                                int i0=u%w;
                                int j0=u/w;
                                REP(d,4) {
                                        int i1=i0+dx[d];
                                        int j1=j0+dy[d];
                                        if (i1>=0 && i1<w && j1>=0 && j1<h) {
                                                int v=j1*w+i1;
                                                int ff=max(a[v],f[u]);
                                                if (ff<f[v]) {
                                                        f[v]=ff;
                                                        q.insert(P(f[v],v));
                                                }
                                        }
                                }
                        }
                }
        }
        printf("%d\n",ans);
        return 0;
}

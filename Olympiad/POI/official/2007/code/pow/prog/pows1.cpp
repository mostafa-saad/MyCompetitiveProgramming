/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pows1.cpp                                                  *}
{*   Autor:   Marek Zylak                                                *}
{*   Opis:    Rozwiazanie wolne, z przeszukiwaniem w g³±b. Czas dzia³ania*}
{*            da sie w prosty sposob oszacowac przez O(n* m * max_h)     *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <complex>

using namespace std;

#define REP(i,n) for (int _tmp_##i=(int)(n),i=0;i<_tmp_##i;i++)
#define FOR(i,a,b) for (int _tmp_##i=(int)(b),i=(a);i<=_tmp_##i;i++)
#define FORD(i,a,b) for (int _tmp_##i=(int)(b),i=(a);i>=_tmp_##i;i--)

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

        int *q=new int[4*n];

        int ans=0;
        FOR(k,1,inf-1) while (head[k]>=0) {
                int x=head[k];
                head[k]=next[x];

                if (f[x]>a[x]) {
                        f[x]=a[x];
                        ans++;
                        int sp=0;
                        q[sp++]=x;
                        while (sp>0) {
                                int u=q[--sp];
                                int i0=u%w;
                                int j0=u/w;
                                int z[4],zc=0;
                                REP(d,4) {
                                        int i1=i0+dx[d];
                                        int j1=j0+dy[d];
                                        if (i1>=0 && i1<w && j1>=0 && j1<h) {
                                                int v=j1*w+i1;
                                                int ff=max(a[v],f[u]);
                                                if (ff<f[v]) {
                                                        f[v]=ff;
                                                        z[zc++]=v;
                                                }
                                        }
                                }
                                FORD(i,zc,2) FOR(j,1,i-1) if (f[z[j-1]]<f[z[j]]) swap(z[j-1],z[j]);
                                FOR(i,1,zc-1) assert(f[z[i-1]]>=f[z[i]]);
                                REP(i,zc) q[sp++]=z[i];
                        }
                }
        }
        printf("%d\n",ans);
        return 0;
}

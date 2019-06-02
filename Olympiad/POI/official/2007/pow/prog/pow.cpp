/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pow.cpp                                                    *}
{*   Autor:   Marek Zylak                                                *}
{*   Opis:    Rozwi±zanie wzorcowe O(n * m + max_wys_gory)               *}
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
#define FORD(i,a,b) for (int _tmp_##i=(int)(a),i=(b);i>=_tmp_##i;i--)

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

        int *next[2];
        REP(i,2) next[i] = new int[n];

        int *head[2];
        REP(i,2) head[i] = new int[inf+1];
        REP(i,2) FOR(j,1,inf) head[i][j]=-1;

        REP(i,n) if (c[i]) {
                next[1][i]=head[1][a[i]];
                head[1][a[i]]=i;
        }

        int ans=0;
        FOR(k,1,inf) while (head[0][k]>=0 || head[1][k]>=0) {
                int l=0;
                if (head[0][k]<0) l=1;

                int x = head[l][k];
                head[l][k]=next[l][x];

                if (l==0 || f[x]==inf) {
                        if (l==1) {
                                ans++;
                                f[x]=a[x];
                        }
                        int i0=x%w;
                        int j0=x/w;
                        REP(d,4) {
                                int i1=i0+dx[d];
                                int j1=j0+dy[d];
                                if (i1>=0 && i1<w && j1>=0 && j1<h) {
                                        int y=j1*w+i1;
                                        if (f[y]==inf) {
                                                f[y]=max(a[y],f[x]);
                                                next[0][y]=head[0][f[y]];
                                                head[0][f[y]]=y;
                                        }
                                }
                        }
                }
        }
        printf("%d\n",ans);

        delete[] a;
        delete[] c;
        delete[] f;
        REP(i,2) delete[] next[i];
        REP(i,2) delete[] head[i];
        return 0;
}

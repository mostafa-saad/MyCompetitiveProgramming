/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    powb1.cpp                                                  *}
{*   Autor:   Marek Zylak                                                *}
{*   Opis:    Rozwi±zanie niepoprawne - zawsze zwraca ilo¶æ pól          *}
{*            Bajtogrodu podzielon± przez 2                              *}
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

        int k=0;
        REP(i,n) k+=c[i];

        printf("%d\n",k/2);

        return 0;
}

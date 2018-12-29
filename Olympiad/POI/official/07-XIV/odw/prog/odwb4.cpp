/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odwb4.cpp                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiązanie sumujące wytrymałości kontenerów w 1 kontener  *}
{*            i pakujące odważniki od najmniejszych                      *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

typedef long long LL;
#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<n; ++i)
#define FOR(var,pocz,koniec) for (int var=pocz; var<=koniec; ++var)
#define FORD(var,pocz,koniec) for (int var=pocz; var>=koniec; --var)
#define VAR(v,i) __typeof(i) v=(i)
#define PB push_back
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

int n, m;
LL sukon;
int odw[100*1000];


int main(void){
    scanf("%d%d", &n, &m);
    REP(i, n){
        int a;
        scanf("%d", &a);
        sukon += (LL)a;
    }
    REP(i, m) scanf("%d", &odw[i]);
    sort(odw, odw+m);
    int i = 0;
    while (i < m && (LL)odw[i] <= sukon) 
        sukon -= (LL)odw[i++];
    printf("%d\n", i);
    return 0;
}

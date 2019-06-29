/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws1.cpp                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Najbardziej prymitywne rozwiązanie brutalne. Probuje kazda *}
{*            konfiguracje                                               *}
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
int odw[100*1000];
int kon[100*1000];
int wynik;

void probuj(int nr, int gleb){
    if (nr == m)
        wynik = max(gleb, wynik);
    else{
        probuj(nr+1, gleb);
        REP(i, n) if (kon[i] >= odw[nr]){
            kon[i] -= odw[nr];
            probuj(nr+1, gleb+1);
            kon[i] += odw[nr];
        }
    }
}

int main(void){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &kon[i]);
    REP(i, m) scanf("%d", &odw[i]);
    probuj(0, 0);
    printf("%d\n", wynik);
    return 0;
}

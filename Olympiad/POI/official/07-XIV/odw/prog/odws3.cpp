/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws3.cpp                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie, które dla każdej permutacji odważników,       *}
{*            zachłannie wkłada je do kolejnych pojemników               *}
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
int bylo[100*1000];
int perm[100*1000];
int wynik;

void umieszczaj(void){
    int i = 0;
    REP(j, n){
        int a = kon[j];
        while (i < m && a >= perm[i])
            a-= perm[i++];
    }
    if (wynik < i) wynik = i;
}

void probuj(int poz){
    if (poz == m)
        umieszczaj();
    else REP(i, m) if (!bylo[i]){
        bylo[i] = 1;
        perm[poz] = odw[i];
        probuj(poz+1);
        bylo[i] = 0;
    }
}


int main(void){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &kon[i]);
    REP(i, m) scanf("%d", &odw[i]);
    probuj(0);
    printf("%d\n", wynik);
    return 0;
}

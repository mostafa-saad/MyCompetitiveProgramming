/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws2.cpp                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Odrobine lepszy rozwiazanie brutalne. Wpierw kubelkuje     *}
{*            odwazniki, i probuje kazda mozliwa liczbe odwaznikow do    *}
{*            kontenera                                                  *}
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

int wartosc[32];
int licznosc[32];
int k;

void probuj(int konid, int odwid, int gleb){
    if (konid == n)
        wynik = max(gleb, wynik);
    else if (odwid == k)
        probuj(konid+1, 0, gleb);
    else{
        int i;
        for(i = 0; licznosc[odwid] >= 0 && 0 <= kon[konid]; ++i){
            probuj(konid, odwid+1, gleb+i);
            kon[konid] -= wartosc[odwid];
            licznosc[odwid]--;
        }
        kon[konid] += wartosc[odwid] * i;
        licznosc[odwid] += i;
    }
}

int main(void){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &kon[i]);
    REP(i, m) scanf("%d", &odw[i]);
    sort(odw, odw+m);
    REP(i, m)
        if (!i || odw[i] != odw[i-1]){
            wartosc[k++] = odw[i];
            licznosc[k-1] = 1;
        }else
            licznosc[k-1]++;
    
    probuj(0, 0, 0);
    printf("%d\n", wynik);
    return 0;
}

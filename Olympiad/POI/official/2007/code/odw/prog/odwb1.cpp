/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odwb1.cpp                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Prosta heurystyka: robimy wyszukiwanie binarne jak w       *}
{*            rozwiazaniu wzorcowym, ale "upychamy" klocki po prostu     *}
{*            w kontenerach, po jednym w kontenerze.                     *}
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

bool probuj(int c){
    FORD(i, c, 0)
        if (odw[i] > kon[n-c+i-1]) return false;
    return true;
}

int main(void){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &kon[i]);
    REP(i, m) scanf("%d", &odw[i]);
    sort(odw, odw+m);
    sort(kon, kon+n);
    if (odw[0] > kon[n-1]){
       printf("0\n");
        return 0;
    }
    int p = 0, k = m;
    while (p+1 < k){
        int c = (p+k)/2;
        if (probuj(c)) p = c;
        else k = c;
    }
    printf("%d\n", p+1);
    return 0;
}

/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw3.cpp                                                   *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie O((n+m)log n log m), czyli wyszukiwanie binarne*}
{*            + zachlanne pobieranie od najwiekszego pojemnika, z        *}
{*            wykorzystaniem wlasnego kopca                              *}
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

int kopiec[100*1000+1];
int kopn;

void upheap(int a){
    int x = kopiec[a];
    while (a > 1){
        if (kopiec[a>>1] >= x) break;
        kopiec[a] = kopiec[a>>1];
        a>>=1;
    }
    kopiec[a] = x;
}

void downheap(int a){
    int x = kopiec[a];
    while ((a<<1) <= kopn){
        int e = a << 1;
        if (e < kopn && kopiec[e] < kopiec[e+1]) ++e;
        if (kopiec[e] <= x) break;
        kopiec[a] = kopiec[e];
        a = e;
    }
    kopiec[a] = x;
}

void inicjuj(void){
    REP(i, n) kopiec[i+1] = kon[i];
    kopn = n;
    FORD(i, n, 1) downheap(i);
}

bool probuj(int c){
    inicjuj();
    FORD(i, c, 0){
        if (kopn == 0) return false;
        int co = kopiec[1];
        if (co < odw[i]) return false;
        kopiec[1] = kopiec[kopn--];
        downheap(1);
        co -= odw[i];
        if (co){
            kopiec[++kopn] = co;
            upheap(kopn);
        }
    }
    return true;
}

int main(void){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &kon[i]);
    REP(i, m) scanf("%d", &odw[i]);
    sort(odw, odw+m);
    int najw = kon[0];
    REP(i, m) najw = max(najw, kon[i]);
    if (odw[0] > najw){
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

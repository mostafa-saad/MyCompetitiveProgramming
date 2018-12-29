/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw2.cpp                                                   *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie O((n+m)log n log m), czyli wyszukiwanie binarne*}
{*            + zachlanne pobieranie od najwiekszego pojemnika, z        *}
{*            wykorzystaniem priority_queue z STLa                       *}
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
    priority_queue<int, vector<int> > q;
    REP(i, n) q.push(kon[i]);
    FORD(i, c, 0){
       if (q.size() == 0) return false;
       int co = q.top();
       if (co < odw[i]) return false;
       q.pop();
       co -= odw[i];
       if (co) q.push(co);
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

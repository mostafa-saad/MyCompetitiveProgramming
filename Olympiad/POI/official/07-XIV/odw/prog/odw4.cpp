/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw4.cpp                                                   *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie O((n+m)log n log m), czyli wyszukiwanie binarne*}
{*            + zachlanne pobieranie od najwiekszego pojemnika, ale z    *}
{*            "kubelkami" z listami pojemnikow                           *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
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
int wartosci[32];
int licznosc[32];
int przelicznik[32];
int k;

void wczytaj_odwazniki(void){
    int wart[32];
    int ile[32];
    REP(i, 32) ile[i] = 0, wart[i] = -1;
    REP(i, m){
        unsigned int a, b;
        scanf("%u", &a);
        b = a;
        int logarytm = 0;
        if (b & 0xffff0000U){
            b >>= 16U;
            logarytm += 16;
        }
        if (b & 0xff00U){
            b >>= 8U;
            logarytm += 8;
        }
        if (b & 0xf0U){
            b >>= 4U;
            logarytm += 4;
        }
        if (b & 0xcU){
            b >>= 2U;
            logarytm += 2;
        }
        if (b & 0x2U){
            b >>= 1U;
            logarytm++;
        }
        wart[logarytm] = a;
        ile[logarytm]++;
    }
    REP(i, 32) if (wart[i] >= 0){
      wartosci[k] = wart[i];
      licznosc[k] = ile[i];
      ++k;
    }
    przelicznik[0] = wartosci[0];
    FOR(i, 1, k-1)
        przelicznik[i] = wartosci[i] / wartosci[i-1];
}

int pojemniki[100*1000];
int lista[100*1000];
int ostlisty[32];
int poczatki[32];

inline int kubelek_pojemnika(int najw, int wlk){
    int p = 0, ko = najw;
    while (p < ko){
        int c = (p+ko+1)/2;
        if (wlk < wartosci[c]) ko = c-1;
        else p = c;
    }
    return p;
}

int licz[32];
int nk;
int poj[100*1000];
bool probuj(int c){
    nk = 0;
    while(c > 0){
        licz[nk] = min(c, licznosc[nk]);
        c -= licz[nk];
        nk++;
    }
    REP(i, nk) poczatki[i] = -1;
    REP(i, n) if(pojemniki[i] > 0){
        int nr = kubelek_pojemnika(nk-1, pojemniki[i]);
        if (poczatki[nr] == -1) 
            ostlisty[nr] = i;
        lista[i] = poczatki[nr];
        poczatki[nr] = i;
        poj[i] = pojemniki[i];
    }
    FORD(i, nk-1, 0){
        while(licz[i]--){
            if (poczatki[i] == -1)
                return false;
            int nr = poczatki[i];
            poczatki[i] = lista[nr];
            poj[nr] -= wartosci[i];
            if (poj[nr] == 0)
                continue;
            int nnr = kubelek_pojemnika(i, poj[nr]);
            if (poczatki[nnr] == -1)
                ostlisty[nnr] = nr;
            lista[nr] = poczatki[nnr];
            poczatki[nnr] = nr;
        }
        if (i && poczatki[i] >= 0){
              if (poczatki[i-1] == -1) ostlisty[i-1] = ostlisty[i];
              lista[ostlisty[i]] = poczatki[i-1];
              poczatki[i-1] = poczatki[i];
        }
    }
    return true;
}

int main(){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &pojemniki[i]);
    wczytaj_odwazniki(); 
    REP(i, n) pojemniki[i] /= wartosci[0];
    FORD(i, k-1, 0) wartosci[i] /= wartosci[0];
    int p = 0, ko = m;
    while (p < ko){
        int c = (p+ko+1)/2;
        if (probuj(c)) p = c;
        else ko = c-1;
    }
    printf("%d\n", p);
    return 0;
}
     

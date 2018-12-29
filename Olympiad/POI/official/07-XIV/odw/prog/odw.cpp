/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw.cpp                                                    *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie wzorcowe. Rozwiazanie rozkladajace pojemniki   *}
{*            na "system" o podstawie odwaznikow                         *}
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

LL rozklad[32];
int pojemniki[100*1000];
int main(){
    scanf("%d%d", &n, &m);
    REP(i, n) scanf("%d", &pojemniki[i]);
    wczytaj_odwazniki(); 
    REP(i, n){
        int a = pojemniki[i];
        REP(j, k){
            a /= przelicznik[j];
            if (j < k-1)
                rozklad[j] += (LL)(a % przelicznik[j+1]);
            else
                rozklad[j] += (LL)a;
        }
    }
    int wynik = 0;
    REP(i, k){
        int j = i;
        int a = licznosc[i];
        int mnoznik = 1;
        while (j < k && a > 0){
            int ile = (int)min((LL)a, (LL)mnoznik * (LL)rozklad[j]);
            wynik += ile;
            a -= ile;
            rozklad[j] -= (ile + mnoznik - 1) / mnoznik;
            ++j;
            if (j < k) 
                mnoznik *= przelicznik[j];
        }
    }
    printf("%d\n", wynik);
    return 0;
}

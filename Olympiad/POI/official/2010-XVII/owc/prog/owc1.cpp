/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owc1.cpp                                         *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *                      Rozwiazanie ze spamiętywaniem liczb Catalana.    *
 *   Zlozonosc czasowa: O(n * k + n^3)                                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>

#define MAXN 600
#define MAXK 20000

int n, m, k;
int x[MAXN], y[MAXN]; // wierzcholki pastwiska
int px[MAXK], py[MAXK]; // owce
int fp[MAXN][MAXN]; // [i][j] -> ile owiec w trojkacie i, j-1, j
int f[MAXN][MAXN]; // [i][j] -> ile owiec w wielokacie i, i+1, ..., j
bool przekatna[MAXN][MAXN]; // czy przekatna jest ok (nie ma owiec na niej i nie dzieli na obszary o nieparzystej ilosci owiec)
int wart[MAXN][MAXN]; // do spamietywania wartosci funkcji licz
bool czyObl[MAXN][MAXN]; // czy obliczono wartosc
int c[MAXN]; // liczba catalana modulo m

int det(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

// na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon
int licz(int pocz, int kon)
{
    if (f[pocz][kon] == 0)
        return c[kon-pocz-1];
    if (kon - pocz <= 2) return 1;
    if (!czyObl[pocz][kon]) {
        int ret = 0;

        for (int i = pocz + 1; i < kon; i++)
            if (przekatna[pocz][i] && przekatna[kon][i])
                ret = (ret + licz(pocz, i)*licz(i, kon)) % m;
        
        wart[pocz][kon] = ret;
        czyObl[pocz][kon] = true;
    }
    
    return wart[pocz][kon];
}

int main() {
    int foo = scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < n; i++)
        foo = scanf("%d%d", &x[i], &y[i]);
    for (int i = 0; i < k; i++) {
        foo = scanf("%d%d", &px[i], &py[i]);
    }
    
    memset(przekatna, true, sizeof(przekatna));
    
    for (int j = 0; j < k; j++) {
        int t = 1;
        for (int i = 0; i < n; i++) {
            int d;
            while (t != i && (d=det(x[i], y[i], x[t], y[t], px[j], py[j]))<=0) {
                if (d==0)
                    przekatna[i][t]=przekatna[t][i] = false;
                t = (t+1)%n;
            }
            if (t != i)
                fp[i][t]++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        int suma = 0;
        for (int dl = 2; dl < n; dl++) {
            suma += fp[i][(i+dl)%n];
            f[i][(i+dl)%n] = suma;
            if (suma%2 != 0)
                przekatna[i][(i+dl)%n]=przekatna[(i+dl)%n][i] = false;
        }
    }
    
    c[0] = 1;
    for (int i = 1; i < n-2; i++)
        for (int j = 0; j < i; j++)
            c[i] = (c[i] + c[j]*c[i-j-1])%m;
    
    printf("%d\n", licz(0, n-1));
    return 0;
}

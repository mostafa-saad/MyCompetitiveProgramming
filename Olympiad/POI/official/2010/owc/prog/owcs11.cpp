/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owcs11.cpp                                       *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *   Zlozonosc czasowa: O(n * k * log k + n^3)                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 600
#define MAXK 20000

using namespace std;

int n, m, k;
int x[MAXN], y[MAXN]; // wierzcholki pastwiska
pair<int, int> p[MAXK]; // owce
int fp[MAXN][MAXN]; // [i][j] -> ile owiec w trojkacie i, j-1, j
bool przekatna[MAXN][MAXN]; // czy przekatna jest ok (nie ma owiec na niej i nie dzieli na obszary o nieparzystej ilosci owiec)
pair<int, int> aktP; //  punkt, wedlug ktorego sortujemy katowo
int wart[MAXN][MAXN]; // do spamietywania wartosci funkcji licz
bool czyObl[MAXN][MAXN]; // czy obliczono wartosc

int det(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

bool comp(pair<int, int> p1, pair<int, int> p2) {
    return det(aktP.first, aktP.second, p1.first, p1.second, p2.first, p2.second) < 0;
}

// na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon
int licz(int pocz, int kon)
{
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
        int px, py;
        foo = scanf("%d%d", &px, &py);
        p[i] = make_pair(px, py);
    }
    
    memset(przekatna, true, sizeof(przekatna));
    
    for (int i = 0; i < n; i++) {
        aktP = make_pair(x[i], y[i]);
        sort(p, p+k, comp);
        
        int j = 0, a = (i+2)%n;
        while (a != i) {
            int d = det(x[i], y[i], x[a], y[a], p[j].first, p[j].second);
            while (j < k && d > 0) {
                fp[i][a]++;
                j++;
                d = det(x[i], y[i], x[a], y[a], p[j].first, p[j].second);
            }
            if (d==0)
                przekatna[i][a]=przekatna[a][i] = false;
            a = (a+1)%n;
        }
    }
    
    for (int i = 0; i < n; i++) {
        int suma = 0;
        for (int dl = 2; dl < n; dl++) {
            suma += fp[i][(i+dl)%n];
            if (suma%2 != 0)
                przekatna[i][(i+dl)%n]=przekatna[(i+dl)%n][i] = false;
        }
    }
    
    printf("%d\n", licz(0, n-1));
    return 0;
}

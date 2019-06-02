/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owcs3.cpp                                        *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Rozwiazanie ze spamietywaniem wartosci           *
 *                      dla wielokata a, a+1, ..., b-1, b.               *
 *   Zlozonosc czasowa: O(n^3 * k)                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define MAXN 600
#define MAXK 20000

int n, m, k;
int x[MAXN], y[MAXN]; // wierzcholki pastwiska
int px[MAXK], py[MAXK]; // owce
int wart[MAXN][MAXN]; // do spamietywania wartosci funkcji licz
bool czyObl[MAXN][MAXN]; // czy obliczono wartosc

int abs(int a) {
    if (a < 0)
        return -a;
    return a;
}

int det(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

// czy dany punkt jest wewnatrz danego trojkata
bool wewnatrz(int x1, int y1, int x2, int y2, int x3, int y3, int xa, int ya)
{
    return abs(det(x1, y1, x2, y2, x3, y3)) ==
        abs(det(xa, ya, x2, y2, x3, y3)) + abs(det(x1, y1, xa, ya, x3, y3)) + abs(det(x1, y1, x2, y2, xa, ya));
}

// czy w trojkacie a, b, c jest parzysta liczba owiec
int sprawdz(int a, int b, int c) {
    int ile = 0;
    for (int i = 0; i < k; i++)
        if (wewnatrz(x[a], y[a], x[b], y[b], x[c], y[c], px[i], py[i]))
            ile++;
    return 1 - ile%2;
}

// czy na danej krawedzi nie ma zadnych owiec
int sprawdzKrawedz(int a, int b)
{
    for (int i = 0; i < k; i++)
        if (det(px[i], py[i], x[a], y[a], x[b], y[b])==0)
            return 0;
    return 1;
}

// na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon
int licz(int pocz, int kon)
{
    if (!czyObl[pocz][kon]) {
        if (kon - pocz <= 1) wart[pocz][kon] = 1;
        else if (kon - pocz == 2) wart[pocz][kon] = sprawdzKrawedz(pocz, kon)*sprawdz(pocz, pocz+1, kon);
        else {
            int ret = 0;
    
            for (int i = pocz + 1; i < kon; i++)
                ret = (ret + sprawdz(pocz, i, kon)*sprawdzKrawedz(pocz, kon)*licz(pocz, i)*licz(i, kon)) % m;
            
            wart[pocz][kon] = ret;
        }
        czyObl[pocz][kon] = true;
    }
    
    return wart[pocz][kon];
}

int main() {
    int foo = scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < n; i++)
        foo = scanf("%d%d", &x[i], &y[i]);
    for (int i = 0; i < k; i++)
        foo = scanf("%d%d", &px[i], &py[i]);
    
    printf("%d\n", licz(0, n-1));
    return 0;
}

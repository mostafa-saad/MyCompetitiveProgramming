/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owcs7.cpp                                        *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Ze spamietywaniem wartosci dla polplaszczyzn     *
 *                      i, j oraz zakazanych przekatnych.                *
 *   Zlozonosc czasowa: O(n^2 * (n + k))                                 *
 *                                                                       *
 *************************************************************************/
 
#include <cstdio>

#define MAXN 600
#define MAXK 20000

int n, m, k;
int x[MAXN], y[MAXN]; // wierzcholki pastwiska
int px[MAXK], py[MAXK]; // pozycje owiec
int wart[MAXN][MAXN]; // do spamietywania wartosci funkcji licz
bool czyObl[MAXN][MAXN]; // czy obliczono wartosc
int f[MAXN][MAXN]; // ile owiec na polplaszczyznie [i][j]
bool naPrzekatnej[MAXN][MAXN]; // czy cos jest na przekatnej

int det(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
}

// czy w trojkacie a, b, c jest parzysta liczba owiec
int sprawdz(int a, int b, int c) {
    int ile = k - f[a][b] - f[b][c] - f[c][a];
    return 1 - ile%2;
}

// na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon
int licz(int pocz, int kon)
{
    if (!czyObl[pocz][kon]) {
        if (kon - pocz <= 1) wart[pocz][kon] = 1;
        else if (kon - pocz == 2) wart[pocz][kon] = (naPrzekatnej[pocz][kon] ? 0 : sprawdz(pocz, pocz+1, kon));
        else {
            int ret = 0;
    
            for (int i = pocz + 1; i < kon; i++)
                if (!naPrzekatnej[pocz][kon])
                    ret = (ret + sprawdz(pocz, i, kon)*licz(pocz, i)*licz(i, kon)) % m;
            
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
    
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            for (int z = 0; z < k; z++) {
                int d = det(x[i], y[i], x[j], y[j], px[z], py[z]);
                if (d == 0)
                    naPrzekatnej[i][j] = naPrzekatnej[j][i] = true;
                else if (d > 0)
                    f[i][j]++;
                else
                    f[j][i]++;
            }
            
    printf("%d\n", licz(0, n-1));
    return 0;
}

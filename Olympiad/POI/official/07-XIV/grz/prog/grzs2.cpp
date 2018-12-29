/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Grzbiety i doliny (GRZ)                                    *}
{*   Plik:    grzs2.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie alternatywne                                   *}
 *            Zlozonosc obliczeniowa: O(n^4)                             *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>

using namespace std;

#define MaxSize 1002

/* Wysokosci poszczegolnych obszarow */
int pola[MaxSize][MaxSize];

int f[MaxSize][MaxSize];
int n;

int Calc() {
    for(int x = n + 1; x >= 0; x--) for(int y = n + 1; y >= 0; y--) f[x][y] = 1;
    for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) pola[x][y] = -pola[x][y];
    for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) {
        for(int x1 = -1; x1 <= 1; x1++) for(int y1 = -1; y1 <= 1; y1++) {
            if (pola[x][y] < pola[x + x1][y + y1]) f[x][y] = 0;
        }
    }
    bool zmiana = 1;
    while(zmiana) {
        zmiana = 0;
        for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) if (f[x][y]) {
            for(int x1 = -1; x1 <= 1; x1++) for(int y1 = -1; y1 <= 1; y1++) {
                if (!f[x + x1][y + y1] && pola[x + x1][y + y1] == pola[x][y]) {
                    f[x][y] = 0;
                    zmiana = 1;
                }
            }
        }
    }
    int wynik = 0;
    zmiana = 1;
    while(zmiana) {
        zmiana = 0;
        for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) if (f[x][y] == 1) {
            f[x][y] = 2;
            wynik++;
            zmiana = 1;
            while(zmiana) {
                zmiana = 0;
                for(int x2 = 1; x2 <= n; x2++) for(int y2 = 1; y2 <= n; y2++) if (f[x2][y2] == 1) {
                    for(int x1 = -1; x1 <= 1; x1++) for(int y1 = -1; y1 <= 1; y1++) if (f[x2 + x1][y2 + y1] == 2) {
                        zmiana = 1;
                        f[x2][y2] = 2;
                    }
                }
            }
            zmiana = 1;
        }
    }
    return wynik;
}

int main() {
    scanf("%d", &n);
    for(int x = n + 1; x >= 0; x--) for(int y = n + 1; y >= 0; y--) pola[x][y] = -2000000000;
    for(int x = n; x > 0; x--) for(int y = n; y > 0; y--) scanf("%d", &pola[x][y]);
    printf("%d %d\n", Calc(), Calc());
    return 0;
}

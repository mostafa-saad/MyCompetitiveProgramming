/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Grzbiety i doliny (GRZ)                                    *}
{*   Plik:    grzb2.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Zlozonosc obliczeniowa: O(n^2) Rozwiazanie nie traktuje    *}
{*            pol po przekatnej jako sasiadujacych                       *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>

using namespace std;

#define MaxSize 1002

/* Wysokosci poszczegolnych obszarow */
int pola[MaxSize][MaxSize];

/* Czy pole zostalo juz odwiedzone */
bool odw[MaxSize][MaxSize];

/* Kolejka do przeszukiwania wszerz */
short posx[MaxSize*MaxSize], posy[MaxSize*MaxSize];

bool SzukajDoliny(int x, int y) {
    posx[0] = x;
    posy[0] = y;
    odw[x][y] = 1;
    int p = 0, k = 1;
    bool wynik = 1;
    while(p < k) {
#define Spr(px, py) if (pola[px][py] > pola[x][y]) wynik = 0; \
    if (!odw[px][py] && pola[px][py] == pola[x][y]) { odw[px][py] = 1; posx[k] = px; posy[k] = py; k++; }

        Spr(posx[p] - 1, posy[p]);
        Spr(posx[p], posy[p] - 1);
        Spr(posx[p], posy[p] + 1);
        Spr(posx[p] + 1, posy[p]);
        p++;
    }
    return wynik;
}

int main() {
    int n, doliny = 0, grzbiety = 0;
    scanf("%d", &n);
    /* Wyczysc tablice odw oraz pola */
    for(int x = n + 1; x >= 0; x--) for(int y = n + 1; y >= 0; y--) {
        odw[x][y] = 0;
        pola[x][y] = -2000000000;
    }
    /* Wczytaj opis krainy */
    for(int x = n; x >= 1; x--) for(int y = n; y >= 1; y--) {
        scanf("%d", &pola[x][y]);
    }
    /* Wyznacz liczbe dolin */
    for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) if (!odw[x][y]) {
        grzbiety += SzukajDoliny(x, y);
    }
    /* Wyczysc tablice odw oraz ustaw obrzeza pola */
    for(int x = n + 1; x >= 0; x--) for(int y = n + 1; y >= 0; y--) odw[x][y] = 0;
    /* Zamien wysokosci pol na przeciwne */
    for(int x = n; x > 0; x--) for(int y = n; y > 0; y--)
        pola[x][y] = -pola[x][y];
    /* Wyznacz liczbe grzbietow */
    for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) if (!odw[x][y]) {
        doliny += SzukajDoliny(x, y);
    }
    /* Wypisz wynik */
    printf("%d %d\n", grzbiety, doliny);
    return 0;
}

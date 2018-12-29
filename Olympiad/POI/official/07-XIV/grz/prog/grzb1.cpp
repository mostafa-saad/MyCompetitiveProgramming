/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Grzbiety i doliny (GRZ)                                    *}
{*   Plik:    grzb1.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Zlozonosc obliczeniowa: O(n^2)                             *}
{*            Rozwiazanie wykorzystujace przeszukiwanie  w glab          *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>

using namespace std;

#define MaxSize 1002

/* Wysokosci poszczegolnych obszarow */
int pola[MaxSize][MaxSize];

/* Czy pole zostalo juz odwiedzone */
bool odw[MaxSize][MaxSize];

/* Wysokosc aktualnie badanego obszaru */
int h;

bool SzukajDoliny(int x, int y) {
    if (pola[x][y] == h && !odw[x][y]) {
        bool wynik = true;
        odw[x][y] = 1;
        wynik &= SzukajDoliny(x - 1, y - 1);
        wynik &= SzukajDoliny(x - 1, y);
        wynik &= SzukajDoliny(x - 1, y + 1);
        wynik &= SzukajDoliny(x, y - 1);
        wynik &= SzukajDoliny(x, y + 1);
        wynik &= SzukajDoliny(x + 1, y - 1);
        wynik &= SzukajDoliny(x + 1, y);
        wynik &= SzukajDoliny(x + 1, y + 1);
        return wynik;
    }
    return (pola[x][y] <= h);
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
        h = pola[x][y];
        grzbiety += SzukajDoliny(x, y);
    }
    /* Wyczysc tablice odw oraz ustaw obrzeza pola */
    for(int x = n + 1; x >= 0; x--) for(int y = n + 1; y >= 0; y--) odw[x][y] = 0;
    /* Zamien wysokosci pol na przeciwne */
    for(int x = n; x > 0; x--) for(int y = n; y > 0; y--)
        pola[x][y] = -pola[x][y];
    /* Wyznacz liczbe grzbietow */
    for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++) if (!odw[x][y]) {
        h = pola[x][y];
        doliny += SzukajDoliny(x, y);
    }
    /* Wypisz wynik */
    printf("%d %d\n", grzbiety, doliny);
    return 0;
}

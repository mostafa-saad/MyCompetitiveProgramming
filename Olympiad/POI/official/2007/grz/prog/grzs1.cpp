/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Grzbiety i doliny (GRZ)                                    *}
{*   Plik:    grzs1.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie alternatywne                                   *}
 *            Zlozonosc obliczeniowa: O(n^2*log(n))                      *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>

using namespace std;

#define MaxSize 1002

/* Wysokosci poszczegolnych obszarow */
int pola[MaxSize][MaxSize];
bool poleOK[MaxSize][MaxSize];
int FaU[MaxSize*MaxSize];
bool grupaOK[MaxSize*MaxSize];
int n;


int Znajdz(int x) {
    return (FaU[x] < 0) ? x : FaU[x] = Znajdz(FaU[x]);
}

void Polacz(int x, int y) {
    x = Znajdz(x);
    y = Znajdz(y);
    if (x != y)
        FaU[x] = y;
}

int Calc() {
    for(int x = n; x > 0; x--) for(int y = n; y > 0; y--) {
        pola[x][y] = -pola[x][y];
        poleOK[x][y] = 1;
    }
    for(int x = 0; x < MaxSize; x++) for(int y = 0; y < MaxSize; y++) {
        grupaOK[x * MaxSize + y] = 0;
        FaU[x * MaxSize + y] = -1;
    }
    for(int x = n; x > 0; x--) 
    for(int y = n; y > 0; y--) 
    for(int x1 = 1; x1 >= -1; x1--)
    for(int y1 = 1; y1 >= -1; y1--) {
        if (pola[x][y] < pola[x + x1][y + y1]) poleOK[x][y] = 0; else
        if (pola[x][y] == pola[x + x1][y + y1]) Polacz(x * MaxSize + y, (x + x1) * MaxSize + y + y1);
    }
    for(int x = n; x > 0; x--) for(int y = n; y > 0; y--) 
        grupaOK[Znajdz(x * MaxSize + y)] = 1;
    for(int x = n; x > 0; x--) for(int y = n; y > 0; y--) if (!poleOK[x][y])
        grupaOK[Znajdz(x * MaxSize + y)] = 0;
    int wynik = 0;
    for(int x = MaxSize * MaxSize - 1; x >= 0; x--) {
        wynik += grupaOK[Znajdz(x)];
        grupaOK[Znajdz(x)] = 0;
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

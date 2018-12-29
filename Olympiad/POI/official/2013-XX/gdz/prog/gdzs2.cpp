/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n*sqrt(n))                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#include "cgdzlib.h"
#include <utility>
#include <vector>
using namespace std;

const int N = 500000;

bool c[N+1];

void koniec(int a, int b) {
    // Znalezlismy 1 i n. Pozostaje ustalic, ktore jest ktore.
    if (g(a, b) == 0)
        odpowiedz(a);
    else
        odpowiedz(b);
}

int main() {
    int n = inicjuj();

    if (n == 1) odpowiedz(1);
    if (n == 2) koniec(1, 2);
    if (n == 3) {
        if (f(1, 2, 2) == 1)
            koniec(1, 2);
        else if (f(1, 3, 2) == 1)
            koniec(1, 3);
        else  // f(2, 3, 2) == 2
            koniec(2, 3);
    }

    int m = 1;
    while (m*m < n) m++;

    // Dzielimy permutacje na sqrt(n) grupek po sqrt(n) elementow kazda. Elementy
    // w obrebie kazdej grupki tworza ciag arytmetyczny o roznicy sqrt(n).

    vector<int> u;  // Lista minimow i maksimow z kazdej grupki

    for (int i = 1; i <= n; ++i)
        c[i] = false;
    for (int i = 1; i <= n; ++i) {
        if (c[i]) continue;  // Kazdy element przetwarzamy tylko raz
        vector<int> v;  // Elementy grupki, do ktorej nalezy p(i)
        for (int j = 1; j <= n; ++j)
            if (f(i, j, m-1) == 1)
                v.push_back(j);
        int delta = (m - 1) * (v.size() - 1);  // Odleglosc miedzy minimum i maksimum
        for (size_t j = 0; j < v.size(); ++j)
            for (size_t k = j + 1; k < v.size(); ++k)
                if (f(v[j], v[k], delta) == 1) {
                    u.push_back(v[j]);
                    u.push_back(v[k]);
                }
        for (size_t j = 0; j < v.size(); ++j)
            c[v[j]] = true;  // Cala grupke oznaczamy jako przetworzona
    }

    // Wsrod krancowych elementow grupek szukamy krancowych elementow permutacji
    for (size_t i = 0; i < u.size(); ++i)
        for (size_t j = i + 1; j < u.size(); ++j)
            if (f(u[i], u[j], n-1) == 1)
                koniec(u[i], u[j]);
}

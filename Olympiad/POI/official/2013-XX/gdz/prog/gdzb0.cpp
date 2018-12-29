/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Uzywa tylko funkcji g                         *
 *                                                                       *
 *************************************************************************/

#include "cgdzlib.h"

int main() {
    int n = inicjuj();

    int best = 1;
    for (int i = 2; i <= n; ++i)
        if (g(i, best) == 0)  // p_i < p_best
            best = i;

    odpowiedz(best);
}

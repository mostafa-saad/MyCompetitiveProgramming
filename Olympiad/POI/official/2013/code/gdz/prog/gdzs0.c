/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include "cgdzlib.h"

int main() {
    int n, i, j;

    n = inicjuj();

    if (n == 1) odpowiedz(1);

    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <= n; ++j)
            if (f(i, j, n - 1) == 1) {  /* Wiemy, ze {p_i, p_j} = {1, n} */
                if (g(i, j) == 0)
                    odpowiedz(i);
                else
                    odpowiedz(j);
            }

    return 1;  // Jesli do tej pory program sie nie skonczyl, cos jest zle
}

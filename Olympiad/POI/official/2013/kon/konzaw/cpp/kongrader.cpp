/* Program oceniajacy do zadania Konewka
 *
 * Czyta ze standardowego wejscia kolejno (wierszami):
 * 1) dwie liczby calkowite N, K,
 * 2) N liczb calkowitych oznaczajacych poczatkowe wysokosci drzew,
 * 3) liczbe naturalna q.
 *
 * Nastepnie czyta q wierszy, w ktorych znajduja sie instrukcje postaci:
 *
 * "p a b" (reprezentujaca wykonanie funkcji "podlej(a,b)")
 * "d a b" (reprezentujaca wykonanie funkcji "dojrzale(a,b)")
 *
 * Program wywoluje odpowiednie funkcje ocenianej biblioteki i wypisuje
 * wyniki funkcji "dojrzale" na standardowe wyjscie */

#include <cstdio>
#include "koninc.h"

const int MAXN = 300000;

int main()
{
    int D[MAXN];
    int num_calls, i;
    int n, k;
    scanf("%d%d", &n, &k);
    for (i = 0; i < n; ++i)
        scanf("%d", &D[i]);

    inicjuj(n,k, D);

    scanf("%d", &num_calls);
    for (i = 1; i <= num_calls; i++)
    {
        char call[2];
        int a, b;
        scanf("%s%d%d", call, &a, &b);
        if (call[0] == 'p')
            podlej(a, b);
        else
            printf("%d\n", dojrzale(a, b));
    }
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Opis:                 Program oceniajacy                            *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include "koninc.h"

int main()
{
    const int MAXN = 300000;
    const int MAGIC = 873454312; /* stala dla kazdego programu */
    const int MAGIC3 = 908903022; /* ostatnia liczba w kazdym tescie */

    int D[MAXN];
    int num_calls, i;
    int n, k, magic;
    scanf("%d%d%d", &n, &k, &magic);
    magic ^= MAGIC;
    n ^= magic;
    k ^= magic;
    for (i = 0; i < n; ++i) {
        scanf("%d", &D[i]);
        D[i] ^= magic;
    }

    inicjuj(n, k, D);

    scanf("%d", &num_calls);
    num_calls ^= magic;
    for (i = 1; i <= num_calls; i++)
    {
        int call;
        int a, b;
        scanf("%d%d%d", &call, &a, &b);
        call ^= magic ^ (i+1);
        a ^= magic;
        b ^= magic;
        if (call == 0)
            podlej(a, b);
        else
            printf("%d\n", dojrzale(a, b)^magic);
    }
    scanf("%d", &magic);
    if (magic != MAGIC3) {
        printf("WRONG: rozwiazanie czytalo dane wejsciowe");
        return 1;
    }
    return 0;
}

/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wags1.c                                                    *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Rozwiązanie powolne - wyczerpujaco generujemy wszystkie    *}
{*            mozliwe ustawienia odwaznikow. Zauwazamy, ze nie ma sensu  *}
{*            nigdy wykorzystywac wiecej niz 2 odwazniki tego samego     *}
{*            rodzaju. Co wiecej nigdy nie ma sensu uzywac odwaznika,    *}
{*            ktory jest rzedu istotnie wiekszego niz dana liczba.       *}
{*            Optymalizacja - jesli juz przekroczylismy dotychczas znale-*}
{*            ziona liczbe odwaznikow, to obcinamy przeszukiwanie.       *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <string.h>

unsigned long long weights[40];
int minneeded = 100000;
int maxorder;
unsigned long count;

void init_weights(void)
{
    int i;
    unsigned long long w = 1;
    for (i=0; i<40; i++) {
        weights[i] = w;
        if (w*4)
            w *= 4;
        else
            w = 0xffffffffffffffffULL;
    }
}

void gen(int order, unsigned long long current, int wcnt)
{
    int i;
    if (wcnt > minneeded)
        return;
    if (current == 0) {
        if (wcnt < minneeded) {
            minneeded = wcnt;
            count = 0;
        }
        count++;
        return;
    }
    if (order > maxorder)
        return;

    i = 0;
    gen(order+1, current + weights[order]*i, wcnt+(i<0?-i:i));
    i = -1;
    gen(order+1, current + weights[order]*i, wcnt+(i<0?-i:i));
    i = 1;
    gen(order+1, current + weights[order]*i, wcnt+(i<0?-i:i));
    i = 2;
    gen(order+1, current + weights[order]*i, wcnt+(i<0?-i:i));
    i = -2;
    gen(order+1, current + weights[order]*i, wcnt+(i<0?-i:i));
}

char st[1010];

int main()
{
    unsigned long long n;

    init_weights();

    /* Symulowane zapetlenie;-) */
    scanf("%s", st);
    if (strlen(st) > 18)
      while (1);
    sscanf(st, "%llu", &n);
    for (maxorder=0; weights[maxorder] < n; maxorder++);

    gen(0, n, 0);
    printf("%lu\n", count);
    return 0;
}


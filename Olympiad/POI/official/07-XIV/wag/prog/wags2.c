/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wags2.c                                                    *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Rozwiązanie powolne - dla kazdej mozliwej sumarycznej wagi *}
{*            odwaznikow na lewej szalce wiemy, ile odwaznikow musi byc  *}
{*            na prawej szalce (tyle, co suma cyfr w zapisie czworkowym);*}
{*            iterujemy wiec po wszystkich wagach lewych szalek.         *}
{*            Najpierw tablicujemy nasze wyniki.                         *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>

unsigned long weights[20];
int maxorder;
unsigned char sumdigits[65536]; /* zmiesci sie w cache'u! */

static inline int stupid_sumdigits(int n) {
    int r = 0;
    while (n) { r += n % 4; n /= 4; }
    return r;
}

void gen_sumdigits(void) {
    int i;
    for (i=0; i<=65535; i++)
        sumdigits[i] = stupid_sumdigits(i);
}

static inline int sumd(int n) {
    return sumdigits[n & 0xffff] + sumdigits[n >> 16];
}

void init_weights(void)
{
    int i;
    unsigned long w = 1;
    for (i=0; i<20; i++) {
        weights[i] = w;
        if (w*4)
            w *= 4;
        else
            w = 0xffffffff;
    }
}

int main()
{
    unsigned long n, i;
    unsigned long maxn;
    int count = 0;
    int nw = 100000;

    init_weights();
    gen_sumdigits();

    scanf("%lu", &n);
    for (maxorder=0; weights[maxorder] < n; maxorder++);
    maxn = weights[maxorder+1];
    for (i=0; i<=maxn; i++) {
        int w = sumd(i) + sumd(n+i);
        if (w > nw) continue;
        if (w == nw) {
            count++;
        } else {
            nw = w;
            count = 1;
        }
    }

    printf("%d\n", count);
    return 0;
}
    

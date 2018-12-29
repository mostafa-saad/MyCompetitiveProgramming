/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wagb1.c                                                    *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Narzucajace sie rozwiazanie niepoprawne.                   *}
{*                                                                       *}
{*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srandom(time(NULL));
    printf("%d\n", (rand()%3) + 1);
    return 0;
}

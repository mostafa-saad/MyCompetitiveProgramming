/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tesb2.cpp                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie niepoprawne.                         *
 *                      Zawsze wypisuje tak.                             *
 *   Złożoność czasowa: O(m + n)                                         *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

int n, m, a;

int main()
{
    scanf("%d", &m);
    for(int i = 0; i < m; ++i)
        scanf("%d", &a);

    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        printf("TAK\n");

    return 0;
}

/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs0.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Znajduje dlugosc pasujacego na danej pozycji   *
 *                        prefiksu, czas O(n^2)                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

int main (void) {
    int n;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    scanf("%s", tekst);

    int *pref = new int[n];

    /* Dla kazdej pozycji szukamy dlugosci prefiksu
    tekstu, ktory zaczyna sie na tej pozycji */
    pref[0]=0;
    for (int i=1; i<n; pref[++i]=0) {
        int j;
        for (j=0; tekst[i+j] == tekst[j]; ++j) ;
        pref[i]=j;
    }
    /* Nastepnie dla kazdej pozycji szukamy najblizszej,
    z ktorej wychodzi prefiks obejmujacy nasza pozycje */
    long long odp=0;
    int max_pref=0;
    for (int i=1; i<n; ++i) {
        /* Najpierw sprawdzamy, czy w ogole istnieje jakis prefiks */
        if (i+pref[i]-1 > max_pref)
            max_pref = i+pref[i]-1;
        if (max_pref < i)
            continue;
        /* A dopiero pozniej szukamy maksymalnego */
        for (int j=i; 2*j >= i; --j)
            if (j+pref[j] > i) {
               odp += j;
               break;
            }
    }

    printf("%lld\n", odp);

    return 0;
}

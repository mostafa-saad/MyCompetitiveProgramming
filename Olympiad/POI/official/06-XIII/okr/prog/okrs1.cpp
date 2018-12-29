/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs0.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie brutalnie poprawne, czas O(n^3)    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

int main (void) {
    int n;
    long long odp=0;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    scanf("%s", tekst);

    /* Dla kazdego prefiksu tekstu szukamy jego maksymalnego okresu */
    for (int i=0; i<n; ++i)
        /* j jest testowana dlugoscia okresu */
        for (int j=i; i <= 2*j; --j) {
            /* Sprawdzamy, czy to j faktycznie odpowiada dobremu okresowi */
            bool ok=true;
            for (int k=0; k <= i-j; ++k)
                if (tekst[k] != tekst[j+k]) {
                   ok=false;
                   break;
                }
            if (ok) {
               odp += j;
               break;
            }
        }

    printf("%lld\n", odp);

    return 0;
}

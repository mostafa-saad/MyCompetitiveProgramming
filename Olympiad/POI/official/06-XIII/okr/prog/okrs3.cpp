/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs3.cpp                                      *
 *   Autor:               Szymon W¹sik                                   *
 *   Opis:                Rozwiazanie brutalne, z uzyciem funkcji        *
 *                        haszujacych, poprawne, czas pesymistycznie     *
 *                        O(n^3), srednio O(n^2).                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define MAXH (1000 * 1000 * 1000)

using namespace std;

int main (void) {
    int n;
    long long odp=0;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    int *hash = new int[n+1];
    scanf("%s", tekst);

    /* Oblicz wartosc funkcji haszujacej dla kazdego prefiksu */
    hash[0] = 0;
    for (int i=1; i<=n; i++)
      hash[i] = (hash[i-1] + i * tekst[i-1]) % MAXH;
    /* Dla kazdego prefiksu tekstu szukamy jego maksymalnego okresu */
    for (int i=0; i<n; ++i)
    {
        /* j jest testowana dlugoscia okresu */
        int sum = 0, hval = 0;
        for (int j=i; i <= 2*j; --j) {
            /* Sprawdzamy, czy to j faktycznie odpowiada dobremu okresowi */
            sum += tekst[j];
            hval += sum;
            hval %= MAXH;
            sum %= MAXH;
            if (hval != hash[i-j+1])
              continue;
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
    }

    printf("%lld\n", odp);

    return 0;
}

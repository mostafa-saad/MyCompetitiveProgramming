/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrb2.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie niepoprawne, wzorowane na          *
 *                        zwyklym O(n^3), testujace tylko bardzo dlugie  *
 *                        okresy)                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

const int Max = 50000000;	//maksymalna liczba "operacji", ktore godzimy sie wykonac

int main (void) {
    int n;
    long long odp=0;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    scanf("%s", tekst);

    /* Dla kazdego prefiksu tekstu szukamy jego maksymalnego okresu */
    int max = Max/n;
    for (int i=0; i<n; ++i)
        /* j jest testowana dlugoscia okresu */
        for (int j=i; (i <= 2*j) && (i-j <= max); --j) {
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

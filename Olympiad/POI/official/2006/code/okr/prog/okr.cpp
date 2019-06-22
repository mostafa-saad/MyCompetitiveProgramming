/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okr.cpp                                        *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie optymalne.                         *
 *                        Zlozonosc obliczeniowa O(n)                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

void LiczP (char tekst[], int P[], int n) {
     P[0] = P[1] = 0;
     int t=0;
     for (int i=2; i <= n; ++i) {
         while ((t != 0) && (tekst[i] != tekst[t+1])) t=P[t];
         if (tekst[i] == tekst[t+1]) ++t;
         P[i]=t;
     }
}

int main (void) {
    int n;
    long long odp=0;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    scanf("%s", tekst);

    int *P = new int[n+1], *MinP = new int[n+1];
    /* cofamy, zeby, jak w podrecznikowych algorytmach,
    indeksowac litery slowa od 1, a nie od 0 */
    --tekst;

    LiczP(tekst, P, n);
    for (int i=1; i <= n; MinP[++i]=0) {
        if (!P[i]) continue;
        if (!P[P[i]])
           MinP[i]=P[i];
        else
           MinP[i]=MinP[ P[i] ];
        odp += i-MinP[i];
    }
    printf("%lld\n", odp);

    return 0;
}

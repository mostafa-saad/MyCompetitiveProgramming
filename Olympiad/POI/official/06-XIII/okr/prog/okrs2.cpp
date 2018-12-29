/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs2.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie O(n^2), modyfikacja rozwiazanie    *
 *                        brutalnego, hashuje lancuchy                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

using namespace std;

int BASE = 26,
    PRIME = 3021377;

int main (void) {
    int n;
    long long odp=0;
    scanf("%d", &n);
    char *tekst = new char[n+1];
    scanf("%s", tekst);

    /* Dla kazdego prefiksu tekstu szukamy jego maksymalnego okresu
       Aby sprawdzac, czy dany prefiks jest jednoczesnie sufiksem dla
    odpowiedniego slowa, wykorzystujemy hashowanie lancucha:
       hash(c0, c1, ..., ck) = (c0 + c1*BASE + ... + ck*BASE^k) % PRIME */
    for (int i=0; i<n; ++i) {
        int pref_hash=0, suf_hash=0, d=1;
        /* j jest testowana dlugoscia okresu */
        for (int j=i; i <= 2*j; --j) {
            pref_hash = (pref_hash + (tekst[i-j]-'a')*d) % PRIME;
            suf_hash = (BASE*suf_hash + (tekst[j]-'a')) % PRIME;
            d = (BASE*d) % PRIME;
            if (pref_hash == suf_hash) {
                bool ok=true;
                for (int k=0; k<=i-j; ++k)
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
    }

    printf("%lld\n", odp);

    return 0;
}

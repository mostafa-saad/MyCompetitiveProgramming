/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(q * n)                                      *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

int t[300000], N, K;

void inicjuj(int n, int k, int *D) {
    N = n, K = k;
    for (int i = 0; i < n; ++i)
        t[i] = D[i];
}

void podlej(int a, int b) {
    for(int i = a; i <= b; ++i)
        t[i]++;
}

int dojrzale(int a, int b) {
    int ile = 0;
    for(int i = a; i <= b; ++i)
        ile += (t[i] >= K);
    return ile;
}

/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdej pozycji ustala liczbe operacji     *
 *                         x_{i+1} += x_i.                               *
 *                         Wykorzystuje jedynie obserwacje o wykonywaniu *
 *                         operacji od lewej do prawej i nieoplacalnosci *
 *                         wybrania zadnej pozycji wiecej niz dwa razy.  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>
#include <cassert>
using namespace std;
const int INFI = 1000000005;

const int MAXN = 1000*1000+9;
int DATA[MAXN];
int COPY[MAXN];
int N;

int check(unsigned l) {
    int m = 0;
    copy(DATA, DATA+N, COPY);
    for (int i = 0; i < N; ++i) {
        COPY[i+1] += COPY[i] * (l % 3);
        m += l % 3;
        l /= 3;
    }

    if (adjacent_find(COPY, COPY+N, greater<int>()) == COPY+N) {
        return m;
    } else
        return INFI;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", DATA+i);
    int wyn = INFI;
    unsigned int _3n = 1; // pow(3U, N);
    for (int i = 0; i < N; ++i)
        _3n *= 3;

    assert(_3n > 0);
    for (unsigned int i=0; i < _3n; ++i) {
        wyn = min(check(i), wyn);
    }
    if (wyn == INFI)
        puts("BRAK");
    else
        printf("%d\n", wyn);
}

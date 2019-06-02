/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(2n!)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Zaklada, że zadnej operacji na danej pozycji  *
 *                         nie wykonamy wiecej niż 2 razy - sprawdza     *
 *                         wszystkie permutacje kolejnosci ruchow.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;
typedef vector<int> VI;
const int INFI = 1000000005;

const int MAXN = 1000*1000+9;
int DATA[MAXN];
int COPY[MAXN];
int N;

int check(const VI perm) {
    copy(DATA, DATA+N, COPY);

    for (int i = 0; i < (int) perm.size(); ++i) {
        COPY[perm[i]+1] += COPY[perm[i]];
        // Znajdz pierwsza pozycje spelniajaca x_i > x_{i+1}
        if (adjacent_find(COPY, COPY+N, greater<int>()) == COPY+N) {
            return i+1;
        }
    }
    return INFI;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", DATA+i);
    VI v;
    for (int i = 0; i < 2*N-2; ++i)
        v.push_back(i/2);

    if (adjacent_find(DATA, DATA+N, greater<int>()) == DATA+N) {
        puts("0");
        return 0;
    }

    int wyn = INFI;
    do {
        wyn = min(check(v), wyn);
    } while (next_permutation(v.begin(), v.end()));

    if (wyn == INFI)
        puts("BRAK");
    else
        printf("%d\n", wyn);
}

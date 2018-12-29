/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Rozpatruje wszystkie pary                     *
 *                         (liczba_jedynek, liczba_zer)                  *
 *                                                                       *
 *************************************************************************/

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const int INFI = 1000000005;


const int MAXN = 1000*1000+9;
int DATA[MAXN];
int SUMS[MAXN]; //sumy prefiksowe
int L0[MAXN]; // sumy prefiksowe liczby zer
int N;

inline void compsums() {
    SUMS[0] = DATA[0];
    L0[0] = DATA[0] == 0;
    for (int i = 1; i <= N; ++i) {
        SUMS[i] = DATA[i] + SUMS[i-1];
        L0[i] = (DATA[i] == 0) + L0[i-1];
    }
}

// Suma na [a, b), assert(a <= b)
inline int sum(int a, int b) {
    assert(a <= b);
    return a ? SUMS[b-1] - SUMS[a-1] : (b ? SUMS[b-1] : 0);
}
inline int zeros(int a, int b) {
    assert(a <= b);
    return a ? L0[b-1] - L0[a-1] : (b ? L0[b-1] : 0);
}

int check(int l_1, int l0) {
    int m = 0;

    // Poprawiamy -1
    if (l_1 && DATA[0] != -1)
        return INFI;

    m += l_1 + sum(0, l_1);

    // Poprawiamy pierwszy element i sprawdzamy zera
    if (l0 && DATA[l_1] != 0) {
        if (DATA[l_1] == 1 && l_1) {
            m += 1;
        } else
            return INFI;
    }

    // Sprawdzamy czy w przedziale sa same zera
    if (l0 && zeros(l_1+1, l_1+l0) != l0-1)
        return INFI;

    // Poprawiamy -1
    int l1 = N - l_1 - l0, l1s = l_1 + l0;
    if (l1 && DATA[l1s] != 1)
        return INFI;

    m += l1 - sum(l1s, N);

    return m;
}

int main() {
    iostream::sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> DATA[i];

    compsums();
    int wyn = INFI;
    for (int l_1 = 0; l_1 <= N; ++l_1)
        for (int l0 = 0; l0 <= N-l_1; ++l0)
            wyn = min(check(l_1, l0), wyn);

    if (wyn == INFI)
        cout << "BRAK" << endl;
    else
        cout << wyn << endl;
}

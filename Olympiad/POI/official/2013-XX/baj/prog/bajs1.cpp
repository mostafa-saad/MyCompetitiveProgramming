/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Rozpatruje wszystkie pary                     *
 *                         (liczba_jedynek, liczba_zer)                  *
 *                         i dla każdej z nich symuluje operacje         *
 *                                                                       *
 *************************************************************************/

#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>
using namespace std;
const int INFI = 1000000005;

const int MAXN = 1000*1000+9;
int DATA[MAXN];
int COPY[MAXN];
int N;

int check(int l_1, int l0) {
    int m = 0;
    copy(DATA, DATA+N, COPY);

    // Poprawiamy -1
    if (l_1 && COPY[0] != -1)
        return INFI;

    for (int i = 1; i < l_1; ++i) {
        m += 1 + COPY[i];
        COPY[i] += COPY[i-1] * (1+COPY[i]);
    }

    // Poprawiamy pierwszy element i sprawdzamy zera
    if (l0 && COPY[l_1] != 0) {
        if (COPY[l_1] == 1 && l_1) {
            m += 1;
            COPY[l_1] += COPY[l_1-1];
        } else
            return INFI;
    }

    // all_of(COPY+l_1, COPY+l_1+l0, bind1st(equals<int>(), 0))
    for (int i = l_1; i < l_1+l0; ++i) if (COPY[i] != 0)
            return INFI;


    // Poprawiamy -1
    int l1 = N - l_1 - l0, l1s = l_1 + l0;
    if (l1 && COPY[l1s] != 1)
        return INFI;

    // By for nie wchodzil na ujemne indeksy
    if (l1s == 0)
        l1s = 1;

    for (int i = l1s; i < N; ++i) {
        m += 1 - COPY[i];
        COPY[i] += COPY[i-1] * (1-COPY[i]);
    }

    // Sanity check
    assert(adjacent_find(COPY, COPY+N, greater<int>()) == COPY+N);

    return m;
}

int main() {
    iostream::sync_with_stdio(0);
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> DATA[i];

    int wyn = INFI;
    for (int l_1 = 0; l_1 <= N; ++l_1)
        for (int l0 = 0; l0 <= N-l_1; ++l0)
            wyn = min(check(l_1, l0), wyn);

    if (wyn == INFI)
        cout << "BRAK" << endl;
    else
        cout << wyn << endl;
}

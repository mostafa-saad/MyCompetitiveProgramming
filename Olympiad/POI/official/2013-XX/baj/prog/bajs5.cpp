/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n * log n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Koniec przedzialu zer znajduje wyszukiwaniem  *
 *                         binarnym.                                     *
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
int SUMS[MAXN]; // Sumy prefiksowe
int LX[MAXN]; // Prefiksowe sumy liczby nie-zer
int N;

inline void compsums() {
    SUMS[0] = DATA[0];
    LX[0] = DATA[0] != 0;
    for (int i = 1; i <= N; ++i) {
        SUMS[i] = DATA[i] + SUMS[i-1];
        LX[i] = (DATA[i] != 0) + LX[i-1];
    }
}

// Suma na [a, b), assert(a <= b)
inline int sum(int a, int b) {
    assert(a <= b);
    return a ? SUMS[b-1] - SUMS[a-1] : (b ? SUMS[b-1] : 0);
}
inline int nonzeros(int a, int b) {
    assert(a <= b);
    return a ? LX[b-1] - LX[a-1] : (b ? LX[b-1] : 0);
}

int search(int p) {
    int b = p,e = N;
    while (b<e) {
        int mid = (b+e)/2;
        if (nonzeros(p, mid+1) == 0) // nie uwzglednia mid+1
            b = mid + 1;
        else
            e = mid;
    }
    return e;
}
// Sprawdza czy mozna dokonczyc jedynkami [l1s, N)
int check1(int l1s) {
    int l1 = N - l1s;
    if (!l1 || (l1 && DATA[l1s] == 1))
        return l1 - sum(l1s, N);
    else
        return INFI;
}

// Sprawdzamy liczbę -1, liczbę 0 wyszukujemy binarnie
int check(int l_1) {
    int m = 0;

    // Poprawiamy -1
    if (l_1 && DATA[0] != -1)
        return INFI;

    m += l_1 + sum(0, l_1);

    if (l_1 == N)
        return m;

    int m1 = m, m2 = m;
    // m1 = nie próbujemy 0
    m1 += check1(l_1);

    // m2 -> znajdujemy najdłuższy przedział 0
    // Poprawiamy pierwszy element
    if (DATA[l_1] != 0) {
        if (DATA[l_1] == 1 && l_1) {
            m2 += 1;
        } else
            return m1;
    }

    // Pozycja końca samych 0 (tj. pierwszego nie-0)
    int l1s = search(l_1+1);

    // Poprawiamy 1
    m2 += check1(l1s);

    return min(m1, m2);
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> DATA[i];
    compsums();
    int wyn = INFI;
    for (int l_1 = 0; l_1 <= N; ++l_1)
        wyn = min(check(l_1), wyn);


    if (wyn == INFI)
        cout << "BRAK" << endl;
    else
        cout << wyn << endl;
}

/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Taksowki                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n!)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie nieoptymalne,                     *
 *                         sprawdzenie wszystkich permutacji taksowek    *
 *                                                                       *
 *************************************************************************/

#include<algorithm>
#include<iostream>
using namespace std;

const int MAX = 500000;

long long taksowki[MAX];

int n;
long long m, d;

int solve() {
    // nasza aktualna pozycja
    long long pozycja = 0;
    for(int i=0; i<n; ++i)
    {
        // sprawdzamy czy i-ta taksowka
        // jest w stanie do nas dojechac
        // i jesli nie to nie jestesmy w stanie dojechac do celu
        if(d-pozycja > taksowki[i])
            return -1;
        // w przeciwnym wypadku jedziemy ile mozemy
        pozycja += (taksowki[i] - (d-pozycja));
        if(pozycja >= m) return i+1;
        if(pozycja > d)
            pozycja = d;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> m >> d >> n;
    for(int i=0; i<n; ++i)
        cin >> taksowki[i];
    sort(taksowki, taksowki+n);
    int wynik = -1;
    do
    {
        int t = solve();
        if(t != -1 && (wynik == -1 || t < wynik))
            wynik = t;
    } while(next_permutation(taksowki, taksowki+n));
    cout << (wynik == -1 ? 0 : wynik) << endl;
    return 0;
}


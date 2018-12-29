/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Taksowki                                      *
 *   Autor:                Igor Adamski                                  *
 *   Opis:                 Rozwiazanie bledne: nie odstawia jednej       *
 *                         taksowki na koncowy przejazd                  *
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
    // jesli zadna taksowka nie jest w stanie
    // dojechac z postoju do celu to zwracamy 0
    if(taksowki[0] < m-d)
        return 0;

    /* Tego nie robimy
     *  // szukamy najmniejszej taksowki, ktora dojedzie
     *  // z postoju do celu
     *  int k = 0;
     *  while(k < n && taksowki[k+1] >= m-d) ++k;
     *  // to bedzie ostatnia taksowka, ktora bedzimey jechac
     *  long long ostatnia = taksowki[k];
     *  // usuwamy ja z ciagu taksowek
     *  while(k+1 < n)
     *  {
     *    taksowki[k] = taksowki[k+1];
     *    ++k;
     *  }
     *  --n;
     */
    // nasza aktualna pozycja
    long long pozycja = 0;
    for(int i=0; i<n; ++i)
    {
        // sprawdzamy czy i-ta taksowka
        // jest w stanie do nas dojechac
        // i jesli nie to nie jestesmy w stanie dojechac do celu
        if(d-pozycja > taksowki[i])
            return 0;
        // w przeciwnym wypadku jedziemy ile mozemy
        pozycja += (taksowki[i] - (d-pozycja));
        // jesli dojechalismy do celu
        if(pozycja >= m)
            return i+1;
        if(pozycja > d)
            pozycja = d;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> m >> d >> n;
    for(int i=0; i<n; ++i)
        cin >> taksowki[i];
    sort(taksowki, taksowki+n, greater<long long>()); // sortujemy malejaco
    cout << solve() << endl;
    return 0;
}


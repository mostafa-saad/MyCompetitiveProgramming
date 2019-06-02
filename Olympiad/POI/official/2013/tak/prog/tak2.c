/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Taksowki                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>

#define MAX 500000

long long taksowki[MAX];
long long tmp[MAX];

int n;
long long m, d;

void sort(int b, int e) {
    if(b+1 == e) return;
    int i, j, k, mid = (b+e)/2;
    sort(b, mid);
    sort(mid, e);
    for(i=b; i<e; ++i)
        tmp[i] = taksowki[i];
    i = b;
    j = mid;
    k = b;
    while(i < mid || j < e)
    {
        if(i == mid || (j < e && tmp[j] > tmp[i]))
            taksowki[k++] = tmp[j++];
        else
            taksowki[k++] = tmp[i++];
    }
}

int solve() {
    int i, k;
    long long ostatnia, pozycja;
    // jesli zadna taksowka nie jest w stanie
    // dojechac z postoju do celu to zwracamy 0
    if(taksowki[0] < m-d)
        return 0;
    // szukamy najmniejszej taksowki, ktora dojedzie
    // z postoju do celu
    k = 0;
    while(k+1 < n && taksowki[k+1] >= m-d) ++k;
    // to bedzie ostatnia taksowka, ktora bedzimey jechac
    ostatnia = taksowki[k];
    // usuwamy ja z ciagu taksowek
    while(k+1 < n)
    {
        taksowki[k] = taksowki[k+1];
        ++k;
    }
    --n;

    // nasza aktualna pozycja
    pozycja = 0;
    for(i=0; i<n; ++i)
    {
        // sprawdzamy czy dojedziemy juz ostatnia taksowka
        if(2LL*(d-pozycja) + m-d <= ostatnia)
            return i+1;
        // jesli nie, to sprawdzamy czy i-ta taksowka
        // jest w stanie do nas dojechac
        // i jesli nie to nie jestesmy w stanie dojechac do celu
        if(d-pozycja > taksowki[i])
            return 0;
        // w przeciwnym wypadku jedziemy ile mozemy
        pozycja += (taksowki[i] - (d-pozycja));
        if(pozycja >= m)
            return i+1;
        if(pozycja > d)
            pozycja = d;
    }
    // po wykorzystaniu n-1 taksowek zostala jeszcze ostatnia
    // wiec sprawdzamy czy mozemy nia dojechac
    if(2LL*(d-pozycja) + m-d <= ostatnia)
        return n+1;
    return 0;
}

int main() {
    int i;
    if(scanf("%lld %lld %d", &m, &d, &n));
    for(i=0; i<n; ++i)
        if(scanf("%lld", taksowki+i));
    sort(0, n);
    printf("%d\n", solve());
    return 0;
}


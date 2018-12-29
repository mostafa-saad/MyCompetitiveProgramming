/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe, wersja ze stosem        *
 *                                                                       *
 *************************************************************************/

#include<iostream>
using namespace std;

const int MAXN = 1000000;

int stos[MAXN+1];
int suma[MAXN+1]; /* suma[i] = stos[1] + stos[2] + ... + stos[i] */
int s;

int wynik[MAXN+1]; /* stos na ktorym beda odkladane kolejne ruchy */
int w; /* szczyt tego stosu */

int n, k;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for(int i=1; i<=n; ++i)
    {
        char z;
        cin >> z;
        int val;
        if(z == 'b') val = 1;
        else val = -k;
        /* Dodanie wartosci na stos */
        ++s;
        stos[s] = i;
        suma[s] = suma[s-1] + val;
        /* Jesli suma k+1 elementow z wierzchu jest rowna 0 to jest to poprawny ruch */
        if(s >= k+1 && suma[s] - suma[s-k-1] == 0) {
            for(int j=0; j<k+1; ++j)
                wynik[w++] = stos[s--];
        }
    }
    for(int i=0; i<n/(k+1); ++i)
    {
        for(int j=0; j<k+1; ++j)
            cout << wynik[--w] << ' ';
        cout << "\n";
    }
    return 0;
}


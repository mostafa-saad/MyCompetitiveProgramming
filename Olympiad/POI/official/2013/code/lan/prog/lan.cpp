/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Lancuch kolorowy                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include<iostream>

using namespace std;

const int N = 1000 * 1000;

int n, m, d; // dlugosc lancucha, dlugosc opisu, dlugosc ladnego fragmentu
int l[N], c[N];
int lancuch[N], ile_w_kolorze[N], ile_ma_byc[N];
int ile_niezgodnosci, wynik;

void akt_kolor(int k, int dodaj) { // dodaj = +1 : dodajemy ogniwo w kolorze k, dodaj = -1 : odejmujemy
    if(ile_w_kolorze[k] == ile_ma_byc[k]) ile_niezgodnosci++;
    ile_w_kolorze[k] += dodaj;
    if(ile_w_kolorze[k] == ile_ma_byc[k]) ile_niezgodnosci--;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> l[i];
        d += l[i];
        if(d > n) {
            cout << 0 << endl;
            return 0;
        }
    }
    for(int i = 0; i < m; i++) {
        cin >> c[i];
        c[i]--;
    }
    for(int i = 0; i < m; i++)
        ile_ma_byc[c[i]] = l[i];
    for(int i = 0; i < n; i++) {
        cin >> lancuch[i];
        lancuch[i]--;
    }

    ile_niezgodnosci = m;
    for(int i = 0; i < d; i++)
        akt_kolor(lancuch[i], 1);
    if(ile_niezgodnosci == 0) wynik++;
    for(int i = 0; i + d < n; i++) {
        akt_kolor(lancuch[i], -1);
        akt_kolor(lancuch[i + d], 1);
        if(ile_niezgodnosci == 0) wynik++;
    }

    cout << wynik << endl;

    return 0;
}

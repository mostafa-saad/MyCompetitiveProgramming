/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Jacek Tomasiewicz                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zapomina o ciagach zaczynajacych sie jedynka  *
 *                                                                       *
 *************************************************************************/

#include <iostream>
using namespace std;

int n, pocZer, pocJedynek, wynik, wynik_tmp, wynik_tmpA, wynik_tmpB, ileZer;
const int N = 1000000;
int ciag[N + 2], ujemne[N + 2], dodatnie[N + 2], zerowe[N + 2], maxZero[N + 2];

int main() {
    cin >> n;
    for (int k = 1; k <= n; k++)
        cin >> ciag[k];
    for (int k = 1; k <= n; k++) {
        ujemne[k] = ujemne[k-1];
        if (ciag[k] == -1) ujemne[k]++;
        dodatnie[k] = dodatnie[k-1];
        if (ciag[k] == 1) dodatnie[k]++;
        zerowe[k] = zerowe[k-1];
        if (ciag[k] == 0) zerowe[k]++;
    }
    ileZer = 0;
    for (int k = n; k >= 1; k--) {
        if (ciag[k] == 0) ileZer++;
        else ileZer = 0;
        maxZero[k] = ileZer;
    }
    ciag[n + 1] = 1;
    int wynik = N * 2;
    for (int k = 0; k <= n; k++) {
        wynik_tmp = 0;
        if (ciag[1] == -1) {
            wynik_tmp += 2 * (dodatnie[k] - dodatnie[0]);
            wynik_tmp += (zerowe[k] - zerowe[0]);
            pocZer = k + 1;
        } else pocZer = 1;
        // przypadek A -1-1|0000|111
        pocJedynek = pocZer + maxZero[pocZer];
        if (ciag[pocJedynek] == 1) {
            wynik_tmpA = wynik_tmp;
            wynik_tmpA += 2 * (ujemne[n] - ujemne[pocJedynek - 1]);
            wynik_tmpA += (zerowe[n] - zerowe[pocJedynek - 1]);
            wynik = min(wynik, wynik_tmpA);
        }
        // przypadek B -1-1|1000|111
        if (ciag[pocZer] == 1) {
            wynik_tmpB = wynik_tmp + 1;
            pocJedynek = pocZer + 1 + maxZero[pocZer + 1];
            if (ciag[pocJedynek] == 1) {
                wynik_tmpB += 2 * (ujemne[n] - ujemne[pocJedynek - 1]);
                wynik_tmpB += (zerowe[n] - zerowe[pocJedynek - 1]);
                wynik = min(wynik, wynik_tmpB);
            }
        }
    }
    if (wynik == N * 2) cout << "BRAK\n";
    else cout << wynik << endl;
    return 0;
}

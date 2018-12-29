/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                         Dla kazdej pozycji obliczamy najdluzszy       *
 *                         zaczynajacy sie i konczacy sie w niej podciag,*
 *                         legalny odpowiednio lewo- i prawostronnie.    *
 *                         Nastepnie przegladamy kolejne lewe konce      *
 *                         tych podciagow i w STL-owym secie wyszukujemy *
 *                         najlepsze odpowiadajace im prawe konce.       *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int N = 1000 * 1000;
int n, res, mins;

// first_smaller[i] - min takie j > i, ze ciag i..(j-1) ma wiecej jablek
int first_smaller[N + 1];
// enpts[i] zawiera j jesli i - 1 jest max takim k, ze k..j ma wiecej jablek
vector<int> enpts[N + 1];
// endpoints dla ustalonego i zawiera enpts[0] + enpts[1] + ... + enpts[i]
// (dodawanie zbiorow)
set<int> endpoints;
int last[N + 2], sums[N + 1];
char fruit[N];

// oblicza first_smaller, enpts
void precalc() {

    sums[0] = 0;
    mins = 0;
    for(int i = 1; i <= n; i++) {
        sums[i] = sums[i - 1] + (fruit[i - 1] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
    mins--;
    for(int i = 0; i <= n; i++) last[i] = n + 1;
    for(int i = n; i >= 0; i--) {
        first_smaller[i] = last[sums[i] - 1 - mins];
        last[sums[i] - mins] = i;
    }

    sums[n] = 0;
    mins = 0;
    for(int i = n - 1; i >= 0; i--) {
        sums[i] = sums[i + 1] + (fruit[i] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
    mins--;
    for(int i = 0; i <= n; i++) last[i] = -1;
    for(int i = 0; i <= n; i++) {
        enpts[last[sums[i] - 1 - mins] + 1].push_back(i);
        last[sums[i] - mins] = i;
    }
}

// oblicza wynik
void calc_res() {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < (int)enpts[i].size(); j++) {
            endpoints.insert(enpts[i][j]);
        }
        int r = first_smaller[i] - 1;
        set<int>::iterator it = endpoints.upper_bound(r);
        it--;
        res = max(res, *it - i);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> fruit;
    precalc();
    calc_res();
    cout << res << endl;
    return 0;
}

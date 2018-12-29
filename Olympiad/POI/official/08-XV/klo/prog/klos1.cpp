/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klos1.cpp                                                 *
 *   Autor:    Krzysztof Duleba                                          *
 *   Opis:     Sposrod n stosow klockow wybrac takie k kolejnych, by ich *
 *             wysokosci mozna bylo wyrownac dokladajac lub zdejmujac jak*
 *             najmniejsza liczbe klockow.                               *
 *             Rozwiazanie nieefektywne: utrzymywanie posortowanej       *
 *             tablicy liczb przy oczekiwanym koszcie k/4 operacji na    *
 *             krok.                                                     *
 *                                                                       *
 *************************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int tab[110000];
int tab_sorted[110000];

int tab_tmp[110000];
int nth_element(int *beg, int *end, int n) {
    memcpy(tab_tmp, beg, (end - beg) * sizeof(int));
    nth_element(tab_tmp, tab_tmp + n, tab_tmp + (end - beg));
    return tab_tmp[n];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) scanf("%d", tab + i);

    for (int i = 0; i < k; ++i) tab_sorted[i] = tab[i];
    sort(tab_sorted, tab_sorted + k);

    long long best_error = 100000000000000000LL;
    int best_pos = -1;
    int best_val = -1;

    for (int i = k;; ++i) {
        int med = tab_sorted[k / 2];
        long long cand = 0;
        for (int j = 0; j < k; ++j) {
            if (tab_sorted[j] < med) {
                cand += med - tab_sorted[j];
            } else {
                cand += tab_sorted[j] - med;
            }
        }

        if (cand < best_error) {
            best_error = cand;
            best_pos = i - 1;
            best_val = med;
        }

        if (i == n) break;

        int idx = lower_bound(tab_sorted, tab_sorted + k, tab[i - k]) - tab_sorted;
        tab_sorted[idx] = tab[i];
        if (idx > 0 && tab_sorted[idx] < tab_sorted[idx - 1]) {
            do {
                swap(tab_sorted[idx], tab_sorted[idx - 1]);
                --idx;
            } while (idx > 0 && tab_sorted[idx] < tab_sorted[idx - 1]);
        } else if (idx + 1 < k && tab_sorted[idx] > tab_sorted[idx + 1]) {
            do {
                swap(tab_sorted[idx], tab_sorted[idx + 1]);
                ++idx;
            } while (idx + 1 < k && tab_sorted[idx] > tab_sorted[idx + 1]);
        }
    }

    for (int i = best_pos + 1 - k; i <= best_pos; ++i) {
        tab[i] = best_val;
    }

    printf("%lld\n", best_error);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", tab[i]);
    }
}

/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klos4.cpp                                                 *
 *   Autor:    Krzysztof Duleba                                          *
 *   Opis:     Sposrod n stosow klockow wybrac takie k kolejnych, by ich *
 *             wysokosci mozna bylo wyrownac dokladajac lub zdejmujac jak*
 *             najmniejsza liczbe klockow.                               *
 *             Rozwiazanie nieefektywne: liczenie mediany za ka¿dym      *
 *             razem od nowa (sortujac)                                  *
 *                                                                       *
 *************************************************************************/
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int tab[110000];

int tab_tmp[110000];
int nth_element(int *beg, int *end, int n) {
    memcpy(tab_tmp, beg, (end - beg) * sizeof(int));
    sort(tab_tmp, tab_tmp + (end - beg));
    return tab_tmp[n];
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) scanf("%d", tab + i);

    long long best_error = 1000000000000000LL;
    int best_pos = 0;
    int best_val = - 1;

    for (int i = k - 1; i < n; ++i) {
        int med = nth_element(tab + i + 1 - k, tab + i + 1, k / 2);
        long long cand = 0;
        for (int j = i + 1 - k; j <= i; ++j) {
            if (tab[j] < med) {
                cand += med - tab[j];
            } else {
                cand += tab[j] - med;
            }
        }

        if (cand < best_error) {
            best_error = cand;
            best_pos = i;
            best_val = med;
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

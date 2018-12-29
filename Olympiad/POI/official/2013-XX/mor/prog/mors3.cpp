/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Mateusz Baranowski                            *
 *   Zlozonosc czasowa:    O(k * n^3 * log d)                            *
 *   Zlozonosc pamieciowa: O(n^2 + k)                                    *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Mnozenie macierzy                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, pair<int, pair<int, int> > > opowiesc_t;
vector<opowiesc_t> opowiesci;

void pomnoz(int n, int * A, int * B) {
    int C[n * n];
    for (int i = 0; i < n * n; ++i) C[i] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i * n + j] |= A[i * n + k] && B[k * n + j];
            }
        }
    }
    for (int i = 0; i < n * n; ++i) A[i] = C[i];
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int base[n * n];
    int path[n * n];
    bool mozliwe[k];
    for (int i = 0; i < n * n; ++i) {
        base[i] = 0;
        path[i] = 0;
    }
    while (m-- > 0) {
        int a, b;
        scanf("%d %d", &a, &b);
        --a;
        --b;
        base[a * n + b] = 1;
        base[b * n + a] = 1;
        path[a * n + b] = 1;
        path[b * n + a] = 1;
    }
    for (int i = 0; i < k; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        opowiesci.push_back(make_pair(c, make_pair(i, make_pair(a-1, b-1))));
    }
    sort(opowiesci.begin(), opowiesci.end());
    int potega = 1;
    for (vector<opowiesc_t>::iterator it = opowiesci.begin(); it != opowiesci.end(); ++it) {
        if (it->first != potega) {
            int z = it->first - potega;
            int tab[n * n];
            for (int x = 0; x < n * n; ++x) {
                tab[x] = base[x];
            }
            while (z > 0) {
                if (z % 2) {
                    --z;
                    pomnoz(n, path, tab);
                } else {
                    z >>= 1;
                    pomnoz(n, tab, tab);
                }
            }
            potega = it->first;
        }
        pair<int, int> p = it->second.second;
        mozliwe[it->second.first] = (path[p.first * n + p.second] != 0);
    }
    for (int i = 0; i < k; ++i) {
        printf(mozliwe[i] ? "TAK\n" : "NIE\n");
    }
    return 0;
}

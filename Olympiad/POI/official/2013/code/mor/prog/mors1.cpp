/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Mateusz Baranowski                            *
 *   Zlozonosc czasowa:    O(k(n + m))                                   *
 *   Zlozonosc pamieciowa: O(n + m + k)                                  *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Sprawdza kazda opowiesc osobno                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 10000
#define MAX_M 10000
#define MAX_K 1000000
#define INFTY 1000000000

typedef pair< pair<int, int>, int> przygoda_t;

int n, m, k;
vector<int> szlaki[MAX_N + 1];
vector<przygoda_t> przygody;

void wczytaj_dane() {
    scanf("%d %d %d", &n, &m, &k);
    int u, v, len;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &u, &v);
        szlaki[u].push_back(v);
        szlaki[v].push_back(u);
    }
    for (int i = 0; i < k; ++i) {
        scanf("%d %d %d", &u, &v, &len);
        przygody.push_back(make_pair(make_pair(u, v), len));
    }
}

bool sprawdz_przygode(przygoda_t przygoda) {
    int a = przygoda.first.first;
    int b = przygoda.first.second;
    int c = przygoda.second;
    int odl[2][2 * MAX_N + 1];
    for (int l = 0; l <= n; ++l) {
        odl[0][l] = INFTY;
        odl[1][l] = INFTY;
    }
    int pocz[2], kon[2], q[2][MAX_N];
    pocz[0] = 0;
    kon[0] = 1;
    pocz[1] = 0;
    kon[1] = 0;
    q[0][0] = a;
    int k = 0;
    int d = 1;
    while (pocz[k] < kon[k] && odl[c%2][b] == INFTY) {
        int u = q[k][pocz[k]++];
        vector<int>::const_iterator it;
        for (it = szlaki[u].begin(); it != szlaki[u].end(); ++it) {
            if (odl[1 - k][*it] == INFTY) {
                odl[1 - k][*it] = d;
                q[1 - k][kon[1 - k]++] = *it;
            }
        }
        if (pocz[k] == kon[k]) {
            k = 1 - k;
            ++d;
        }
    }
    return (odl[c%2][b] <= c);
}

int main() {
    wczytaj_dane();
    for (int i = 0; i < k; ++i) {
        if (sprawdz_przygode(przygody[i])) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Mateusz Baranowski                            *
 *   Zlozonosc czasowa:    O(n(n + m) + k)                               *
 *   Zlozonosc pamieciowa: O(n + m + k)                                  *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Dla kazdego wierzcholka szukamy najkrotszej   *
 *                         sciezki dlugosci parzystej i nieparzystej     *
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

typedef pair< pair<int, int>, int> przygody_t;

int n, m, k;
vector<int> szlaki[MAX_N + 1];
vector<przygody_t> przygody;
bool wyniki[MAX_K];

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

void sprawdz_przygody() {
    vector<int> poczatek[MAX_N + 1];
    for (size_t i = 0; i < przygody.size(); ++i) {
        int u = przygody[i].first.first, v = przygody[i].first.second;
        if (poczatek[u].empty()) {
            poczatek[v].push_back(i);
        } else {
            poczatek[u].push_back(i);
        }
    }
    int odl[2][MAX_N + 1];
    for (int i = 1; i <= n; ++i) {
        for (int l = 0; l <= n; ++l) {
            odl[0][l] = INFTY;
            odl[1][l] = INFTY;
        }
        if (!poczatek[i].empty()) {
            int pocz[2], kon[2], q[2][MAX_N + 2];
            pocz[0] = 0;
            kon[0] = 1;
            pocz[1] = 0;
            kon[1] = 0;
            q[0][0] = i;
            int k = 0;
            int d = 1;
            while (pocz[k] < kon[k]) {
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
        }
        vector<int>::const_iterator it;
        for (it = poczatek[i].begin(); it != poczatek[i].end(); ++it) {
            int d = przygody[*it].second;
            int u = przygody[*it].first.first;
            if (u == i) {
                u = przygody[*it].first.second;
            }
            wyniki[*it] = (odl[d % 2][u] <= d);
        }
    }
}

int main() {
    wczytaj_dane();
    sprawdz_przygody();
    for (int i = 0; i < k; ++i) {
        if (wyniki[i]) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }
    return 0;
}

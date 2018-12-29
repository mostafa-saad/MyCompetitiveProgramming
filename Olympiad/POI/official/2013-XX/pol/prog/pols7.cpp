/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^4)                                        *
 *   Zlozonosc pamieciowa: O(n^3)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Programowanie dynamiczne                      *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#define FOREACH(x, v) for(__typeof((v).begin()) x = (v).begin(); x != (v).end(); x++)

using namespace std;

const int N = 100;

int n;
int a, b;
int wynik;

vector<int> g[N]; // Struktura drzewa
bool vis[N];
int stan[N][N + 1][N + 1];
/* stan[v][x][y] = m  oznacza,
 * ze jezeli w poddrzewie T ukorzenionym w v
 * istnieje x sciezek postaci t ---> v
 * oraz     y sciezek postaci v ---> t,
 * gdzie t jest dowolnym wierzholkiem w poddrzewie T,
 * to m jest maksymalnym wynikiem czesciowym dla
 * poddrzewa T. */
int najlepszy[2][N][N + 1];
/* najlepszy[0][v][x] : maksymalny wynik czesciowy dla
 * poddrzewa T ukorzenionego w v przy zalozeniu, ze istnieje w nim
 * x sciezek postaci v ---> t
 * najlepszy[1][v][x] :  --||-- postaci t ---> v */

void dfs(int v) {
    vis[v] = true;

    for(int i = 0; i < 2; i++)
        najlepszy[i][v][1] = 0;
    stan[v][1][1] = 0;

    FOREACH(it, g[v]) if(!vis[*it]) {
        dfs(*it);
        for(int i = n; i >= 1; i--)
            for(int j = n; j >= 1; j--) if(stan[v][i][j] != -1)
                    for(int t = 0; t < 2; t++) // t = 1 ==> krawedz skierowana do v
                        for(int k = 1; k <= n; k++) if(najlepszy[t][*it][k] != -1) {
                                int x = i + t * k, y = j + (1 - t) * k;
                                stan[v][x][y] =
                                    max(stan[v][x][y], stan[v][i][j] + najlepszy[t][*it][k] +
                                        t * k * j + (1 - t) * k * i);
                                najlepszy[0][v][y] = max(najlepszy[0][v][y], stan[v][x][y]);
                                najlepszy[1][v][x] = max(najlepszy[1][v][x], stan[v][x][y]);
                            }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    if(n > N) return 1;
    for(int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 0; i < n; i++)
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++)
                stan[i][j][k] = -1;
            for(int t = 0; t < 2; t++)
                najlepszy[t][i][j] = -1;
        }
    dfs(0);
    for(int i = 1; i <= n; i++) wynik = max(wynik, najlepszy[0][0][i]);
    cout << n - 1 << " " << wynik << endl;

    return 0;
}

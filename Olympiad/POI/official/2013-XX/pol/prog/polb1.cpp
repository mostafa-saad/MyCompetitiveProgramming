/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    Ustalona przez stala M                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Generowanie losowego skierowania krawedzi     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib>
#define FOREACH(x, v) for(__typeof((v).begin()) x = (v).begin(); x != (v).end(); x++)

using namespace std;

const int N = 250000, M = 1000 * 1000;

int n, t;
int a, b;
long long wynik, mx = 0;

long long wyn[N];
bool skier[N];
vector< pair<int, int> > g[N];

void dfs(int v) {
    wyn[v] = 0;
    FOREACH(it, g[v]) if((v < it->first) == (bool)(skier[it->second])) { // Mozna przejsc ta krawedzia
        if(wyn[it->first] == -1) dfs(it->first);
        wyn[v] += 1 + wyn[it->first];
    }
    wynik += wyn[v];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a--, b--;
        g[a].push_back(make_pair(b, i));
        g[b].push_back(make_pair(a, i));
    }

    int m = M / n;

    for(int i = 0; i < m; i++) {
        wynik = 0;
        for(int i = 0; i < n; i++) {
            wyn[i] = -1;
            skier[i] = rand() % 2;
        }
        for(int i = 0; i < n; i++) if(wyn[i] == -1) dfs(i);
        mx = max(mx, wynik);
    }

    cout << n - 1 << " " << mx << endl;

    return 0;
}

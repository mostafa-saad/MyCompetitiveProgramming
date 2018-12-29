/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(2^n * n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Sprawdzamy wszystkie mozliwe skierowania      *
 *                         krawedzi.                                     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#define FOREACH(x, v) for(__typeof((v).begin()) x = (v).begin(); x != (v).end(); x++)

using namespace std;

const int N = 100;

int n;
unsigned int t; // t reprezentuje stan skierowania
int a, b;
int wynik, mn = N * N, mx = 0;

int wyn[N]; // wynik dla poddrzewa
vector< pair<int, int> > g[N];
/* krawedz wychodzaca reprezentowana jako para
(wierzcholek do ktorego prowadzi, indeks) */

void dfs(int v) {
    wyn[v] = 0;
    FOREACH(it, g[v]) if((v < it->first) == (bool)(t & (1 << it->second))) { // Mozna przejsc ta krawedzia
        if(wyn[it->first] == -1) dfs(it->first);
        wyn[v] += 1 + wyn[it->first];
    }
    wynik += wyn[v];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    if(n >= 32) return 1;
    for(int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a--, b--;
        g[a].push_back(make_pair(b, i));
        g[b].push_back(make_pair(a, i));
    }

    for(t = 0; (int)t < (1 << n); t++) {
        wynik = 0;
        for(int i = 0; i < n; i++) wyn[i] = -1;
        for(int i = 0; i < n; i++) if(wyn[i] == -1) dfs(i);
        mx = max(mx, wynik);
        mn = min(mn, wynik);
    }

    cout << mn << " " << mx << endl;

    return 0;
}

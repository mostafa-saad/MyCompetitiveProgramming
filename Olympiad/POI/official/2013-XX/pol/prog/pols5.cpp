/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Zamiast szukac centroidu, sprawdzamy          *
 *                         wszystkie wierzcholki.                        *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#define FOREACH(x, v) for(__typeof((v).begin()) x = (v).begin(); x != (v).end(); x++)

using namespace std;

const int N = 250000;

int n;
int a, b;
int kandydat;
long long wynik, najlepszy;

int sz[N];// sz - wielkosc poddrzewa
vector<int> wielk; // wielkosci poddrzew synow centroidu

unsigned int mozliwe[N]; // Osiagalne wielkosci trzymane na masce bitowej

vector<int> g[N]; // Drzewo

void dfs(int v) {
    sz[v] = 1;
    FOREACH(it, g[v]) if(sz[*it] == 0) {
        dfs(*it);
        sz[v] += sz[*it];
        wynik += (long long)sz[*it];
    }
}

void dodaj(int x) {
    for(int i = n - 1; i >= 0; i--) if(mozliwe[i]) mozliwe[i + x] = true;
}

int blisko_polowy() {
    /* Zwraca liczbe h taka, ze
        suma wielkosci poddrzew pewnych synow centroidu
        jest rowna h oraz |2 * h - (n - 1)| jest minimalne */
    int h = 0;
    for(int i = 0; i < n; i++) mozliwe[i] = false;
    mozliwe[0] = true;
    FOREACH(it, wielk) {
        dodaj(*it);
    }
    for(int i = 0; 2 * i <= n - 1; i++) if(mozliwe[i]) h = i;
    return h;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(kandydat = 0; kandydat < n; kandydat++) {
        for(int i = 0; i < n; i++) {
            sz[i] = 0;
        }
        wynik = 0;
        wielk.clear();
        dfs(kandydat); // Obliczenie wielkosci poddrzew
        FOREACH(it, g[kandydat]) wielk.push_back(sz[*it]);
        long long h =  blisko_polowy();
        wynik += h * (long long)((n - 1) - h);
        najlepszy = max(najlepszy, wynik);
    }

    cout << n - 1 << " " << najlepszy << endl;

    return 0;
}

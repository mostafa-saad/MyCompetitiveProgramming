/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zakladamy, ze zawsze synow centroidu mozna    *
 *                         podzielic na dwie rowne grupy.                *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#define FOREACH(x, v) for(__typeof((v).begin()) x = (v).begin(); x != (v).end(); x++)

using namespace std;

const int N = 250000;

int n;
int a, b;
int centroid;
long long wynik;

int sz[N], p[N]; // sz - wielkosc poddrzewa, p - rodzic
vector<int> g[N]; // Drzewo

void dfs(int v) {
    sz[v] = 1;
    FOREACH(it, g[v]) if(sz[*it] == 0) {
        dfs(*it);
        p[*it] = v;
        sz[v] += sz[*it];
        wynik += sz[*it];
    }
}

int znajdz_centroid(int v) {
    FOREACH(it, g[v]) if(*it != p[v] && sz[*it] * 2 > n) {
        return znajdz_centroid(*it);
    }
    return v;
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

    dfs(0);
    centroid = znajdz_centroid(0);

    for(int i = 0; i < n; i++) sz[i] = 0;
    wynik = 0;
    dfs(centroid); // Obliczenie wielkosci poddrzew

    long long h =  (n - 1) / 2;
    wynik += h * ((n - 1) - h);

    cout << n - 1 << " " << wynik << endl;

    return 0;
}

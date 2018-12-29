/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Trzymamy osiagalne wartosci na masce bitowej  *
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
vector<int> wielk; // wielkosci poddrzew synow centroidu

int nn;// nn - liczba blokow w masce bitowej
unsigned int mozliwe[N]; // Osiagalne wielkosci trzymane na masce bitowej

vector<int> g[N]; // Drzewo

void dfs(int v) {
    sz[v] = 1;
    FOREACH(it, g[v]) if(sz[*it] == 0) {
        dfs(*it);
        p[*it] = v;
        sz[v] += sz[*it];
        wynik += (long long)sz[*it];
    }
}

int znajdz_centroid(int v) {
    FOREACH(it, g[v]) if(*it != p[v] && sz[*it] * 2 > n) {
        return znajdz_centroid(*it);
    }
    return v;
}

void dodaj(int x) {
    int d1 = x / 32, d2 = x % 32;
    for(int i = nn - 1; i >= 0; i--) {
        if(d2 != 0) mozliwe[i + d1 + 1] |= mozliwe[i] >> (32 - d2); // Kolejnosc wykonywania tych linijek ma znaczenie, bo moze zajsc d1 = 0
        mozliwe[i + d1] |= mozliwe[i] << d2;
    }
}

int blisko_polowy() {
    /* Zwraca liczbe h taka, ze
        suma wielkosci poddrzew pewnych synow centroidu
        jest rowna h oraz |2 * h - (n - 1)| jest minimalne */
    int h = 0;
    nn = n / 32 + 1;
    mozliwe[0] = 1; // Ustawiamy najmniej znaczacy bit

    FOREACH(it, wielk) {
        dodaj(*it);
    }
    for(int i = 0; 2 * i <= n - 1; i++) if(mozliwe[i / 32] & (1 << (i % 32))) h = i;
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

    dfs(0);
    centroid = znajdz_centroid(0);

    for(int i = 0; i < n; i++) sz[i] = 0;
    wynik = 0;
    dfs(centroid); // Obliczenie wielkosci poddrzew

    FOREACH(it, g[centroid]) wielk.push_back(sz[*it]);
    long long h =  blisko_polowy();
    wynik += h * (long long)((n - 1) - h);

    cout << n - 1 << " " << wynik << endl;

    return 0;
}

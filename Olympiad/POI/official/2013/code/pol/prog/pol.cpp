/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n*sqrt(n))                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
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
int wielk[N]; // wielk[s] - liczba synow centroidu o poddrzewach wielkosci s
int nowy_moz[2][N];
bool mozliwe[N];
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

int blisko_polowy() {
    /* Zwraca liczbe h taka, ze
        suma wielkosci poddrzew pewnych synow centroidu
        jest rowna h oraz |2 * h - (n - 1)| jest minimalne */
    int h = 0;
    mozliwe[0] = 1;

    for(int i = 1; i < n; i++) if(wielk[i] > 0) {
            int k1 = 0, k2 = 0;
            for(int j = n - 1; j >= 0; j--) if(mozliwe[j] && !mozliwe[j + i]) {
                    /* zaznaczamy nowe mozliwe wielkosci zbiorow po dodaniu i-tego poddrzewa */
                    nowy_moz[0][k1++] = j + i;
                    mozliwe[j + i] = true;
                }
            for(int l = 2; l <= wielk[i]; l++) {
                /* dodajemy pozostale poddrzewa o wielkosci i */
                for(int m = 0; m < k1; m++) if(!mozliwe[nowy_moz[0][m] + i]) {
                        nowy_moz[1][k2++] = nowy_moz[0][m] + i;
                        mozliwe[nowy_moz[0][m] + i] = true;
                    }
                for(int m = 0; m < k2; m++) nowy_moz[0][m] = nowy_moz[1][m];
                k1 = k2, k2 = 0;
            }
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

    dfs(0);
    centroid = znajdz_centroid(0);

    for(int i = 0; i < n; i++) sz[i] = 0;
    wynik = 0;
    dfs(centroid); // Obliczenie wielkosci poddrzew

    FOREACH(it, g[centroid]) wielk[sz[*it]]++; // 1 <= sz[v] <= n - 1 dla kazdego v
    long long h =  blisko_polowy();
    wynik += h * (long long)((n - 1) - h);

    cout << n - 1 << " " << wynik << endl;

    return 0;
}

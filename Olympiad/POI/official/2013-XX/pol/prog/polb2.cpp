/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zamiast centroidu szukamy centrum             *
 *                         (srodka srednicy) drzewa.                     *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#define FOREACH(x, v) for(__typeof((v).begin()) x = (v).begin(); x != (v).end(); x++)

using namespace std;

const int N = 250000;

int n;
int a, b;
vector<int> centrum; // jedno lub dwa
long long wynik, najlepszy;

int najdluzsza[N], sciezka[N], srednica, poczatek;
int sz[N]; // sz - wielkosc poddrzewa, p - rodzic
int wielk[N]; // wielk[s] - liczba synow centrumu o poddrzewach wielkosci s
int nowy_moz[2][N];
bool mozliwe[N];
vector<int> g[N]; // Drzewo

void dfs(int v) {
    sz[v] = 1;
    FOREACH(it, g[v]) if(sz[*it] == 0) {
        dfs(*it);
        sz[v] += sz[*it];
        wynik += (long long)sz[*it];
    }
}

void centrum_dfs(int v) {
    sciezka[v] = 0;
    FOREACH(it, g[v]) if(sciezka[*it] == -1) {
        centrum_dfs(*it);
        if(sciezka[*it] + sciezka[v] + 1 > srednica) {
            srednica = sciezka[*it] + sciezka[v] + 1;
            poczatek = v;
        }
        if(sciezka[*it] + 1 > sciezka[v]) {
            sciezka[v] = sciezka[*it] + 1;
            najdluzsza[v] = *it;
        }
    }
}

vector<int> znajdz_centrum() {
    vector<int> wynik;
    for(int i = 0; i < n; i++) sciezka[i] = -1;
    centrum_dfs(0);
    for(int l = srednica / 2; 2 * l <= srednica; l++) {
        int v = poczatek;
        while(sciezka[v] != l) v = najdluzsza[v];
        wynik.push_back(v);
    }
    return wynik;
}

int blisko_polowy() {
    /* Zwraca liczbe h taka, ze
        suma wielkosci poddrzew pewnych synow centrumu
        jest rowna h oraz |2 * h - (n - 1)| jest minimalne */
    int h = 0;
    for(int i = 0; i < n; i++) mozliwe[i] = false;
    mozliwe[0] = true;

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

    centrum = znajdz_centrum();

    FOREACH(it, centrum) {
        for(int i = 0; i < n; i++) {
            sz[i] = 0;
            wielk[i] = 0;
        }
        wynik = 0;
        dfs(*it); // Obliczenie wielkosci poddrzew

        FOREACH(jt, g[*it]) wielk[sz[*jt]]++; // 1 <= sz[v] <= n - 1 dla kazdego v
        long long h =  blisko_polowy();
        wynik += h * (long long)((n - 1) - h);
        najlepszy = max(najlepszy, wynik);
    }

    cout << n - 1 << " " << najlepszy << endl;

    return 0;
}

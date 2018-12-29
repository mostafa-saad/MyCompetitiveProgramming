/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O((n + q) log n)                              *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Przy aktualizacji drzewa w funkcji zwieksz()  *
 *                         zle liczona jest wartosc nd_w[v]              *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
using namespace std;

const int INF = 1000*1000*1000;
const int M = 524288; // 2^19

int N, K;
int dd[2*M]; // drzewa dojrzale
int nd_w[2*M]; // drzewa niedojrzale - wartosc w wezle
int nd_max[2*M]; // drzewa niedojrzale - max z synow + wartosc dla wezla

/** operacje na drzewach dojrzalych **/

/* wstawia dojrzale drzewo o numerze a */
void wstawDojrzale(int a) {
    int v = M + a;
    dd[v]++;
    while (v != 1) {
        v /= 2;
        dd[v] = dd[2*v] + dd[2*v+1];
    }
}

/* zwraca liczbe dojrzalych drzew na przedziale [a, b] */
int ileDojrzalych(int a, int b) {
    int va = M + a, vb = M + b;
    int wyn = dd[va];
    if (va != vb) wyn += dd[vb];
    while(va / 2 != vb / 2) {
        if (va%2 == 0) wyn += dd[va+1];
        if (vb%2 == 1) wyn += dd[vb-1];
        va /= 2, vb /= 2;
    }
    return wyn;
}

/** operacje na drzewach niedojrzalych */

inline void przesun_nizej(int v) {
    int ile = nd_w[v];
    nd_w[v] = 0;
    nd_w[2*v] += ile;
    nd_max[2*v] += ile;
    nd_w[2*v+1] += ile;
    nd_max[2*v+1] += ile;
}

/* ustawia wysokosc drzewa a na x */
void ustawWysokosc(int a, int x) {
    int v = M + a;
    nd_w[v] = x;
    nd_max[v] = x;
    while (v != 1) {
        v /= 2;
        nd_max[v] = nd_w[v] + max(nd_max[2*v], nd_max[2*v+1]);
    }
}

/* zwieksza o jeden wysokosci drzew na przedziale [p, k] */
void zwieksz(int v, int p, int k, int p_b, int k_b) {
    // v - indeks tablicy odpowiadający przedzialowi bazowemu [p_b, k_b]
    if (k < p_b || k_b < p || p_b > k_b)
        return;

    if (p <= p_b && k_b <= k) {
        nd_w[v]++;
        nd_max[v]++;
        return;
    }

    int m = (p_b + k_b) / 2;
    zwieksz(2*v, p, k, p_b, m);
    zwieksz(2*v+1, p, k, m+1, k_b);

    nd_max[v] = max(nd_max[2*v], nd_max[2*v+1]);
}

/* znajduje dojrzale drzewa wśród wczesniej niedojrzalych (na przedziale [p, k])
 * dodaje je do struktury dla drzew dojrzalych oraz "usuwa" spośród niedojrzalych,
 * ustawiając ich wysokosc na -inf. */
void znajdzDojrzale(int v, int p, int k, int p_b, int k_b) {
    if(nd_max[v] < K || k < p_b || k_b < p || p_b > k_b)
        return;

    if(p_b == k_b) {
        wstawDojrzale(p_b);
        ustawWysokosc(p_b, -INF);
        return;
    }

    if(nd_w[v] > 0)
        przesun_nizej(v);

    int m = (p_b + k_b) / 2;
    znajdzDojrzale(2*v, p, k, p_b, m);
    znajdzDojrzale(2*v+1, p, k, m+1, k_b);
}

/** funkcje **/

void inicjuj(int n, int k, int *D) {
    N = n, K = k;
    for (int i = 0; i < N; ++i) {
        ustawWysokosc(i, D[i]);
    }
}

void podlej(int a, int b) {
    zwieksz(1,a,b,0,M-1);
}

int dojrzale(int a, int b) {
    znajdzDojrzale(1,a,b,0,M-1);
    return ileDojrzalych(a,b);
}

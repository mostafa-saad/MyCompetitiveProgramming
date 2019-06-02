/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs3.cpp                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie dynamiczne O(n^5)                             *
 *                                                                       *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <cstring>

#define MAX_NUM 100
#define MAX_N 100000

unsigned int wynik_tab[8000000];
int x[MAX_N], y[MAX_N];

int ile_x[MAX_NUM], ile_y[MAX_NUM];
int n, m;

inline bool get_wynik(int px, int kx, int py, int ky) {
    int klucz = px*n*m*m + kx*m*m + py*m + ky;
    int ind = klucz / 32;
    int bit = klucz % 32;
    return wynik_tab[ind]&(1<<bit);
}

inline void set_wynik(int px, int kx, int py, int ky, bool wartosc) {
    int klucz = px*n*m*m + kx*m*m + py*m + ky;
    int ind = klucz / 32;
    int bit = klucz % 32;
    if (wartosc)
        wynik_tab[ind] |= (1<<bit);
    else
        wynik_tab[ind] ^= (wynik_tab[ind]&(1<<bit));
}

bool licz(int px, int kx, int py, int ky) {
    int rozne_x = 0, ostatni_x = 0;
    memset(ile_x, 0, sizeof(ile_x));
    for (int i = px; i <= kx; i++) {
        if (!ile_x[x[i]]) {
            rozne_x++;
            ostatni_x = i-1;
        }
        ile_x[x[i]]++;
    }
    
    int rozne_y = 0, ostatni_y = 0;
    memset(ile_y, 0, sizeof(ile_y));
    for (int i = py; i <= ky; i++) {
        if (!ile_y[y[i]]) {
            rozne_y++;
            ostatni_y = i-1;
        }
        ile_y[y[i]]++;
    }
    
    bool czyRozne = (rozne_y != rozne_x);
    for (int i = 0; i < MAX_NUM; i++)
        if (!!ile_x[i] != !!ile_y[i])
            czyRozne = true;
    
    int pierwszy_x = px;
    while (--ile_x[x[pierwszy_x]]) pierwszy_x++;
    pierwszy_x++;
    int pierwszy_y = py;
    while (--ile_y[y[pierwszy_y]]) pierwszy_y++;
    pierwszy_y++;

    return (!czyRozne) && (rozne_x==1 ||
        (get_wynik(px, ostatni_x, py, ostatni_y) /* f(p(x), p(y)) */
        && get_wynik(pierwszy_x, kx, pierwszy_y, ky))); /* f(s(x), s(y)) */
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        memset(ile_x, 0, sizeof(ile_x));
        memset(ile_y, 0, sizeof(ile_y));
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            x[i]--;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &y[i]);
            y[i]--;
        }
        
        for (int dl_x = 1; dl_x <= n; dl_x++)
            for (int dl_y = 1; dl_y <= m; dl_y++)
                for (int px = 0; px+dl_x <= n; px++)
                    for (int py = 0; py+dl_y <= m; py++)
                        set_wynik(px, px+dl_x-1, py, py+dl_y-1, licz(px, px+dl_x-1, py, py+dl_y-1));
        
        printf("%d\n", get_wynik(0, n-1, 0, m-1));
    }
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs5.pas                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie dynamiczne O(n^3*K)                           *
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

inline bool get_wynik(int a, int b, int ile_znakow) {
    int klucz = (ile_znakow-1) * n * m + b * n + a;
    int ind = klucz / 32;
    int bit = klucz % 32;
    return wynik_tab[ind]&(1<<bit);
}

inline void set_wynik(int a, int b, int ile_znakow, bool wartosc) {
    int klucz = (ile_znakow-1) * n * m + b * n + a;
    int ind = klucz / 32;
    int bit = klucz % 32;
    if (wartosc)
        wynik_tab[ind] |= (1<<bit);
    else
        wynik_tab[ind] ^= (wynik_tab[ind]&(1<<bit));
}

bool licz(int px, int py, int ile_znakow) {
    int rozne_x = 0;
    memset(ile_x, 0, sizeof(ile_x));
    for (int i = px; i < n && (rozne_x < ile_znakow || ile_x[x[i]]); i++) {
        if (!ile_x[x[i]]) 
            rozne_x++;
        ile_x[x[i]]++;
    }
    if (rozne_x != ile_znakow) return false;
    int pierwszy_x = px;
    while (--ile_x[x[pierwszy_x]]) pierwszy_x++;
    pierwszy_x++;
    
    int rozne_y = 0;
    memset(ile_y, 0, sizeof(ile_y));
    for (int i = py; i < m && (rozne_y < ile_znakow || ile_y[y[i]]); i++) {
        if (!ile_y[y[i]]) 
            rozne_y++;
        ile_y[y[i]]++;
    }
    if (rozne_y != ile_znakow) return false;
    int pierwszy_y = py;
    while (--ile_y[y[pierwszy_y]]) pierwszy_y++;
    pierwszy_y++;
    
    bool czyRozne = (rozne_y != rozne_x);
    for (int i = 0; i < MAX_NUM; i++)
        if (!!ile_x[i] != !!ile_y[i])
            czyRozne = true;
    
    return (!czyRozne) && get_wynik(px, py, ile_znakow-1) /* f(p(x), p(y)) */
        && get_wynik(pierwszy_x, pierwszy_y, ile_znakow-1); /* f(s(x), s(y)) */
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        int rozne_x = 0, rozne_y = 0;
        memset(ile_x, 0, sizeof(ile_x));
        memset(ile_y, 0, sizeof(ile_y));
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            if (!ile_x[x[i]]) rozne_x++;
            ile_x[x[i]]++;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &y[i]);
            if (!ile_y[y[i]]) rozne_y++;
            ile_y[y[i]]++;
        }
        bool czyRozne = (rozne_y != rozne_x);
        for (int i = 0; i < MAX_NUM; i++)
            if (!!ile_x[i] != !!ile_y[i])
                czyRozne = true;
        
        if (czyRozne) { // W(x) != W(y)
            printf("0\n");
            continue;
        } else if (rozne_x==1) { // |W(x)| = |W(y)| = 1
            printf("1\n");
            continue;
        }
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                set_wynik(i, j, 1, x[i]==y[j]);
        
        for (int ile_znakow = 2; ile_znakow <= rozne_x; ile_znakow++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    set_wynik(i, j, ile_znakow, licz(i, j, ile_znakow));
        
        printf("%d\n", get_wynik(0, 0, rozne_x));
    }
    return 0;
}

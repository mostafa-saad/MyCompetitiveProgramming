/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przs7.cpp                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie generujace graf bezposrednio O(n^2*K)         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>

#define MAX_N 100000
#define MAX_NUM 100
#define TAB_SIZE 100000

int x[MAX_N], y[MAX_N];
int ile[MAX_NUM];
int sufiks[TAB_SIZE];
int prefiks[TAB_SIZE];
int sufiksKraw[TAB_SIZE];
int prefiksKraw[TAB_SIZE];
int wierzcholek[TAB_SIZE];
int ile_wierzch;

#define WIERZCH(pozycja, rozmiar, poziom) (poziom*rozmiar + pozycja)

int budujGraf(int *tab, int n, int p, int dl, int poziom) {
    if (wierzcholek[WIERZCH(p, n, poziom)]!=0)
        return wierzcholek[WIERZCH(p, n, poziom)];
    int akt_wierzch = ile_wierzch++;
    wierzcholek[WIERZCH(p, n, poziom)] = akt_wierzch;
    sufiks[akt_wierzch] = prefiks[akt_wierzch] = -1;
    memset(ile, 0, sizeof(ile));
    for (int i = 0; i < dl; i++)
        ile[tab[i]]++;
    int poz = 0;
    while (--ile[tab[poz]]>0) poz++;
    sufiksKraw[akt_wierzch] = tab[poz];
    int sufiksPoz = poz;
    for (int i = 0; i <= poz; i++)
        ile[tab[i]]++;
    poz = dl-1;
    while (--ile[tab[poz]]>0) poz--;
    prefiksKraw[akt_wierzch] = tab[poz];
    if (poz > 0)
        prefiks[akt_wierzch] = budujGraf(tab, n, p, poz, poziom+1);
    if (sufiksPoz < dl-1)
        sufiks[akt_wierzch] = budujGraf(tab+sufiksPoz+1, n, p+sufiksPoz+1, dl-sufiksPoz-1, poziom+1);
    return akt_wierzch;
}

int porownajGrafy(int vx, int vy)
{
    if (vx==-1 || vy==-1)
        return vx==vy;
    return sufiksKraw[vx]==sufiksKraw[vy] && prefiksKraw[vx]==prefiksKraw[vy]
        && porownajGrafy(sufiks[vx], sufiks[vy])
        && porownajGrafy(prefiks[vx], prefiks[vy]);
}

int main()
{
    int n, m, k;
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            x[i]--;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &y[i]);
            y[i]--;
        }

        ile_wierzch = 0;
        memset(wierzcholek, 0, sizeof(wierzcholek));
        int korzen_x = budujGraf(x, n, 0, n, 0);
        memset(wierzcholek, 0, sizeof(wierzcholek));
        int korzen_y = budujGraf(y, m, 0, m, 0);

        printf("%d\n", porownajGrafy(korzen_x, korzen_y));
    }
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przb2.cpp                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie niepoprawne. Porownuje zbiory liter tylko     *
 *             na pierwszym poziomie rekurencji.                         *
 *                                                                       *
 *************************************************************************/
 
#include <cstdio>
#include <cstring>

#define MAX_N 100000
#define MAX_NUM 100

int x[MAX_N], y[MAX_N];
int ile_x[MAX_NUM], ile_y[MAX_NUM];

int f(int px, int kx, int py, int ky, int depth=0)
{
    if (depth > 1) return 1;
    memset(ile_x, 0, sizeof(ile_x));
    memset(ile_y, 0, sizeof(ile_y));
    int rozne_x = 0, rozne_y = 0;
    int ostatni_x = 0, ostatni_y = 0;
    for (int i = px; i <= kx; i++) {
        if (!ile_x[x[i]]) {
            rozne_x++;
            ostatni_x = i;
        }
        ile_x[x[i]]++;
    }
    for (int i = py; i <= ky; i++) {
        if (!ile_y[y[i]]) {
            rozne_y++;
            ostatni_y = i;
        }
        ile_y[y[i]]++;
    }
    bool czyRozne = (rozne_y != rozne_x);
    for (int i = 0; i < MAX_NUM; i++)
        if (!!ile_x[i] != !!ile_y[i])
            czyRozne = true;
    if (czyRozne)
        return 0;
    if (rozne_x == 1)
        return 1;
    int pierwszy_x = px, pierwszy_y = py;
    while (--ile_x[x[pierwszy_x]]) pierwszy_x++;
    while (--ile_y[y[pierwszy_y]]) pierwszy_y++;
    return f(px, ostatni_x-1, py, ostatni_y-1, depth+1) && f(pierwszy_x+1, kx, pierwszy_y+1, ky, depth+1);
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
        printf("%d\n", f(0, n - 1, 0, m - 1));
    }
    return 0;
}

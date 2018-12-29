/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przb6.cpp                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie niepoprawne. Porownuje ciagi po usunieciu     *
 *             powtorzen                                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>

#define MAX_N 100000

int x[MAX_N], y[MAX_N];

int main()
{
    int n, m, k;
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        int aktX = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &x[aktX]);
            if (aktX==0 || x[aktX]!=x[aktX-1]) aktX++;
        }
        int aktY = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d", &y[aktY]);
            if (aktY==0 || y[aktY]!=y[aktY-1]) aktY++;
        }
        bool rowne = (aktX==aktY);
        if (rowne)
            for (int i = 0; i < aktX; i++)
                rowne |= (x[i]==y[i]);
        printf("%d\n", rowne);
    }
    return 0;
}

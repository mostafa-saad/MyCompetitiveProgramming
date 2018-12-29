/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tess4.cpp                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie powolne.                             *
 *   Złożoność czasowa: O(m * n + l)                                     *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

#define MAX_M 1000000 // maksymalna długość ciągu a_i
#define MAX_A 1000000 // maksymalny wyraz ciągu

int m, n, k, a[MAX_M], b[MAX_M], ia, cou[MAX_A][2];
bool ok;

int main()
{
    for(int i = 0; i < MAX_A; ++i)
        cou[i][0] = cou[i][1] = 0;

    scanf("%d", &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d", &a[i]);
        ++cou[a[i] - 1][0];
    }

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &k);
        ok = true;
        ia = 0;
        for(int j = 0; j < k; ++j) {
            scanf("%d", &b[j]);
            ++cou[b[j] - 1][1];
            if(cou[b[j] - 1][0] < cou[b[j] - 1][1])
                ok = false;
        }
        for(int j = 0; j < k; ++j) {
            if(!ok)
                break;
            while(ia < m && a[ia] != b[j])
                ++ia;
            if(ia == m)
                ok = false;
            ++ia;
        }
        for(int j = 0; j < k; ++j)
            cou[b[j] - 1][1] = 0;
        printf("%s\n", (ok ? "TAK" : "NIE"));
    }
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tesb3.cpp                                        *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie niepoprawne.                         *
 *   Złożoność czasowa: O(m + l + |A|)                                   *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

#define MAX_M 1000000
#define MAX_A 1000000

int n, m, k, a, lic[MAX_A], b[MAX_M], cou[MAX_A];
bool ok;

int main()
{
    for(int i = 0; i < MAX_A; ++i)
        lic[i] = cou[i] = 0;

    scanf("%d", &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d", &a);
        ++lic[a - 1];
    }

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        ok = true;
        scanf("%d", &k);
        for(int j = 0; j < k; ++j) {
            scanf("%d", &b[j]);
            ++cou[--b[j]];
            if(!ok)
                continue;
            if(cou[b[j]] > lic[b[j]])
                ok = false;
        }
        for(int j = 0; j < k; ++j)
            cou[b[j]] = 0;
        printf("%s\n", (ok ? "TAK" : "NIE"));
    }

    return 0;
}

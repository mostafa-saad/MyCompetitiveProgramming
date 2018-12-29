/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Trzy wieze                                         *
 *   Zlozonosc czasowa:    O(n^3)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/
#include <cstdio>
#include <cassert>
#include <algorithm>
const int MAXN = 1000000;

char str[MAXN+1];

bool ok(int i, int j) {
    int c1 = 0, c2 = 0, c3 = 0;

    for (int k=i; k<=j; k++)
        if (str[k] == 'B')
            c1++;
        else if (str[k] == 'C')
            c2++;
        else if (str[k] == 'S')
            c3++;
    
    int zero = (c1 == 0) + (c2 == 0) + (c3 == 0);
    return zero == 2 || (c1 != c2 && c1 != c3 && c2 != c3);	
}

int main() {
    int n;
    assert(scanf("%d%s", &n, str) == 2);
    
    int res = 0;
    for (int i=0; i<n; i++)
        for (int j=i; j<n; j++)
            if (ok(i, j))
                res = std::max(res, j-i+1);
    printf("%d\n", res);
}

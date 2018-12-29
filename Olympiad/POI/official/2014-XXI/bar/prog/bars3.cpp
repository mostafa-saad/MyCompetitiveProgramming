/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego miejsca zapamietujemy najdluzszy  *
 *                         skok jaki mozna zrobic w lewo i w prawo.      *
 *                         Nastepnie sprawdzamy kazdy spojny fragment    *
 *                         w czasie stalym, w kolejnosci rosnacych       *
 *                         dlugosci fragmentow.                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1000*1000;

char s[N];
int n;

int lJump[N], rJump[N];

void preprocess() {
    int nJ, nP, k;
    for (int i = 0; i < n; ++i) {
        nJ = 0, nP = 0, k = 0;
        while (nP >= nJ && i+k < n) {
            if (s[i+k] == 'j') nJ++;
            else nP++;
            k++;
        }
        rJump[i] = k;
        // printf("%d -> %d (%d)\n", i, i+rJump[i]-1, rJump[i]);
    }

    for (int i = 0; i < n; ++i) {
        nJ = 0, nP = 0, k = 0;
        while (nP >= nJ && i-k >= 0) {
            if (s[i-k] == 'j') nJ++;
            else nP++;
            k++;
        }
        lJump[i] = k;
        // printf("%d <- %d (%d)\n", i-lJump[i]+1, i, lJump[i]);
    }
}

inline bool check(int a, int b) {
    return (a + rJump[a]-1 >= b) && (b - lJump[b]+1 <= a);
}

int main() {
    int mx = 0;
    scanf("%d%s", &n, s);
    preprocess();
    for (int k = 1; k <= n; ++k)
        for (int i = 0; i <= n-k; ++i)
            if (s[i] == 'p' && check(i, i+k-1)) {
                mx = k;
                break;
            }
    printf("%d\n", mx);
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Sprawdza kazdy spójny fragment liniowo.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1000*1000;
char s[N];

bool check(int a, int b) {
    int nJ = 0, nP = 0;
    for (int i = a; i <= b; ++i) {
        if (s[i] == 'j') nJ++;
        else nP++;
        if (nP < nJ) return false;
    }
    nJ = 0, nP = 0;
    for (int i = b; i >= a; --i) {
        if (s[i] == 'j') nJ++;
        else nP++;
        if (nP < nJ) return false;
    }
    return true;
}

int main() {
    int n, mx = 0;
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j)
            if (check(i, j))
                mx = max(mx, j-i+1);
    printf("%d\n", mx);
    return 0;
}

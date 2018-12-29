/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1000 * 1000;
int n, res, mins;
// sums[] - sumy prefiksowe
// nxt[i] = min takie j > i, ze sums[i] = sums[j]
// peak[i] = max takie j, ze sums[i] <= sums[k] <= sums[j] dla i < k < j
int sums[N + 1], nxt[N + 1], peak[N + 1];
char fruit[N];

// oblicza tablice sums
void calc_sums() {
    for(int i = 1; i <= n; i++) {
        sums[i] = sums[i - 1] + (fruit[i - 1] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
}

// oblicza tablice nxt
void calc_nxt() {
    int last[N + 1];
    for(int i = 0; i <= n; i++) last[i] = -1;
    for(int i = n; i >= 0; i--) {
        nxt[i] = last[sums[i] - mins];
        last[sums[i] - mins] = i;
    }
}

// oblicza tablice peak oraz wynik
void calc_res() {
    int cpeak = n;
    for(int i = 0; i <= n; i++) peak[i] = i;
    for(int i = n - 1; i >= 0; i--) if(fruit[i] == 'p') {
            if(nxt[i] != -1 && sums[peak[nxt[i]]] >= sums[cpeak]) {
                cpeak = peak[nxt[i]];
            }
            peak[i] = cpeak;
            res = max(res, cpeak - i);
        } else {
            cpeak = i;
        }
}

int main() {
    scanf("%d %s", &n, fruit);
    calc_sums();
    calc_nxt();
    calc_res();
    printf("%d\n", res);
    return 0;
}

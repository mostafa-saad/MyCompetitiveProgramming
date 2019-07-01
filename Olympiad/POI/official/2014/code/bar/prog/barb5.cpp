/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Wyszukiwanie binarne po wyniku                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 1000 * 1000;
int n, res;
char fruit[N];
int first_smaller[2][N + 1];

void calc_nxt() {
    int last[N + 2], sums[N + 1], mins;

    sums[0] = 0;
    mins = 0;
    for(int i = 1; i <= n; i++) {
        sums[i] = sums[i - 1] + (fruit[i - 1] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
    mins--;
    for(int i = 0; i <= n; i++) last[i] = n + 1;
    for(int i = n; i >= 0; i--) {
        first_smaller[0][i] = last[sums[i] - 1 - mins];
        last[sums[i] - mins] = i;
    }

    sums[n] = 0;
    mins = 0;
    for(int i = n - 1; i >= 0; i--) {
        sums[i] = sums[i + 1] + (fruit[i] == 'p' ? 1 : -1);
        mins = min(mins, sums[i]);
    }
    mins--;
    for(int i = 0; i <= n; i++) last[i] = -1;
    for(int i = 0; i <= n; i++) {
        first_smaller[1][i] = last[sums[i] - 1 - mins];
        last[sums[i] - mins] = i;
    }
}

bool sprawdz(int l, int r) {
//	printf("sprawdz (%d, %d)\n", l, r);
    if(first_smaller[0][l] > r + 1 && first_smaller[1][r + 1] < l) {
        res = max(res, r - l + 1);
        return true;
    } else {
        return false;
    }
}

bool sprobuj(int l) {
    for(int i = 0; i + l < n; i++) {
        if(sprawdz(i, i + l)) return true;
    }
    return false;
}

void calc_res() {
    int l = 0, r = n + 1, m;
    while(l < r) {
        m = l + (r - l) / 2;
        if(sprobuj(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
}

int main() {
    scanf("%d %s", &n, fruit);
    calc_nxt();
    calc_res();
    printf("%d\n", res);
    return 0;
}

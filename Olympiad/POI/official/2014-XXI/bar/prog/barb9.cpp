/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Opis:                 Rozwiazanie bledne                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1000 * 1000;
char fruit[N];
int sums[N + 1];
int n, res = 0;
bool good[N];

// oblicza tablice sums
void calc_sums() {
    for(int i = 1; i <= n; i++) {
        sums[i] = sums[i - 1] + (fruit[i - 1] == 'p' ? 1 : -1);
    }
}

void calc_good() {
    int mins = 0;
    for(int i = 0; i < n; i++) {
        mins = min(mins, sums[i]);
        good[i] = mins <= sums[i + 1];
    }
    int maxs = sums[n];
    for(int i = n - 1; i >= 0; i--) {
        if(maxs < sums[i]) good[i] = false;
        maxs = max(sums[i], maxs);
    }
}

void calc_res() {
    int last = 0;
    for(int i = 0; i < n; i++) {
        if(!good[i]) {
            last = i + 1;
        } else {
            res = max(res, i - last + 1);
        }
    }
}


int main() {
    scanf("%d %s", &n, fruit);
    calc_sums();
    calc_good();
    calc_res();
    printf("%d\n", res);
    return 0;
}

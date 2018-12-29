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
char slo[N];
int n, res = 0;

void check(int be, int en, int dir) {
    int sum = -1, mx_sum, last = be;
    for(int i = be; i != en; i += dir) {
        if(slo[i] == 'j') {
            sum--;
        } else {
            if(sum < 0) {
                sum = mx_sum = 1;
                last = i;
            } else {
                sum++;
            }
            mx_sum = max(mx_sum, sum);
            if(sum == mx_sum) {
                res = max(res, abs(i - last) + 1);
            }
        }
    }
}
int main() {
    scanf("%d %s", &n, slo);
    check(0, n, 1);
    check(n - 1, -1, -1);
    printf("%d\n", res);
    return 0;
}

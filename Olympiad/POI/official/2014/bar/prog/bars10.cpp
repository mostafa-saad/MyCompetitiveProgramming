/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    Omega(n sqrt(n))                              *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1000 * 1000;
char s[N];

void check(int be, int en, int dir, bool checked_oppos, int &mx) {
    if((en - be) * dir < 0) return;
//  printf("check [%d %d]\n", be, en);
    int sum = 0, last = be;
    bool good = true;
    for(int i = be; (en - i) * dir >= 0; i += dir) {
        if(s[i] == 'j') {
            if(sum == 0) {
                good = false;
                check(i - dir, last, -dir, true, mx);
            }
            sum--;
        } else {
            if(sum < 0) {
                sum = 0;
                last = i;
            }
            sum++;
        }
    }
    if(good && checked_oppos) {
        mx = max(mx, abs(be - en) + 1);
    } else if(!checked_oppos || last != be) {
        check(en, last, -dir, true, mx);
    }
}

int main() {
    int n, mx = 0;
    scanf("%d %s", &n, s);
    check(0, n - 1, 1, false, mx);
    printf("%d\n", mx);
    return 0;
}

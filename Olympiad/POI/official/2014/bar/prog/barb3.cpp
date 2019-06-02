/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Odcinamy bloki "j" z bokow ciagu, i wykonujemy*
 *                         sprawdzenie. Jesli ciag wciaz jest            *
 *                         niedozwolony, to usuwamy krotszy blok "p"     *
 *                         i powtarzamy do skutku.                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int N = 1000 * 1000;
int n, res;
pair<int, int> p1, p2;
char fruit[N + 1];


bool sprawdz(int l, int r) {
    int ile = 0;
    for(int i = l; i <= r; i++) {
        if(fruit[i] == 'j') {
            ile--;
        } else {
            ile++;
        }
        if(ile < 0) return false;
    }
    ile = 0;
    for(int i = r; i >= l; i--) {
        if(fruit[i] == 'j') {
            ile--;
        } else {
            ile++;
        }
        if(ile < 0) return false;
    }
    res = max(res, r - l + 1);
    return true;
}

void calc_res() {
    int l = 0, r = n - 1;
    while(l <= r) {
        while(l <= r && fruit[l] == 'j') l++;
        while(l <= r && fruit[r] == 'j') r--;
        if(!sprawdz(l, r)) {
            int nl = l, nr = r;
            while(nl <= nr && fruit[nl] == 'p' && fruit[nr] == 'p') {
                nl++, nr--;
            }
            if(fruit[nl] == 'p')
                r = nr;
            else
                l = nl;
        } else {
            break;
        }
    }
}

int main() {
    scanf("%d %s", &n, fruit);
    calc_res();
    printf("%d\n", res);
    return 0;
}

/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(q*3^n)                                      *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Nie korzysta z obserwacji, ze zachlanny       *
 *                         wybor jest optymalny.                         *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 20;
const int Q = 10;

int n, queries, k[Q], p[N], depth[N];

int bitcount[1<<N];
int cache[1<<N];

int curr_k;

int go(int subset) {
    if (cache[subset] != -1) return cache[subset];
    if (subset == 0) return cache[subset] = 0;

    int todo = 0;  // zadania, ktore mozemy wykonac
    for (int i = 0; i < n; ++i) {
        if ((subset & (1<<i)) && (i==0 || !(subset & (1<<p[i])))) {
            todo += (1<<i);
        }
    }

    cache[subset] = n;
    int x = 0;
    do {  // iteracja po wszystkich podzbiorach 'todo'
        if (x > 0 && bitcount[x] <= curr_k)
            cache[subset] = min(cache[subset], 1 + go(subset - x));
        x = (x + 1 + ~todo) & todo;  // a kind of magic
    } while (x!=0);

    return cache[subset];
}

int main() {
    int ret;
    ret = scanf("%d%d", &n, &queries);
    for (int i = 0; i < queries; ++i)
        ret = scanf("%d", &k[i]);
    for (int i = 1; i < n; i++) {
        ret = scanf("%d", &p[i]);
        p[i]--;
    }

    if (n > N) while(true) {}

    for (int i = 0; i < n; i++) depth[i] = 1;
    for (int i = n-1; i > 0; i--)
        depth[p[i]] = 1 + depth[i];

    bitcount[0] = 0;
    for (int i = 1; i < (1<<n); ++i)
        bitcount[i] = bitcount[i >> 1] + (i & 1);

    for (int qi = 0; qi < queries; ++qi) {
        if (qi > 0) printf(" ");
        if (k[qi] >= n) {
            printf("%d", depth[0]);
        } else {
            curr_k = k[qi];
            for (int i = 0; i < (1<<n); ++i) cache[i] = -1;
            printf("%d", go((1<<n) - 1));
        }
    }
    printf("\n");
    if(ret<0) return 0;
    return 0;
}


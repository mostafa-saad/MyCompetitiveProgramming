/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(n log^2 n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Suma na przedziale (a nie minimalna suma suf.)*
 *                         jako kryterium legalnosci skoku w lewo.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1000*1000;
const int MM = (1<<21);

char s[N];
int n;

int sumP[N+1];

/* Rozwiazanie */

int st_sum[N], st_jump[N]; // stos
int st_head = 0;

void preprocess() {
    sumP[0] = 0;
    for (int i = 0; i < n; ++i)
        sumP[i+1] = sumP[i] + s[i] == 'p' ? 1 : -1;
}

inline int sum_query(int a, int b) {
    return sumP[b+1] - sumP[a];
}

int max_left_jump(int k) {
//    printf("stack:");
//    for(int i = 0; i < st_head; ++i)
//        printf(" %d", st_jump[i]);
//    printf(" <- %d\n", k);

    // wyszukujemy najdluzszy skok binarnie
    int b = 0, e = st_head, mid, best = st_head;
    while (b < e) {
        mid = (b + e) >> 1;
        if (sum_query(st_jump[mid], k) >= 0) {
            e = mid - 1;
            best = mid;
        } else {
            b = mid + 1;
        }
    }
    if (best>0 && sum_query(st_jump[best-1], k) >= 0)
        best = best-1;

    return k - st_jump[best] + 1;
}

int main() {
    int mx = 0;
    scanf("%d%s", &n, s);
    preprocess();

    for (int i = 0; i < n; ++i)
        if (s[i] == 'p') {
            st_jump[st_head] = i;
            st_sum[st_head] = 1;
            st_head++;
            mx = max(mx, max_left_jump(i));
        } else {
            while (st_head>0 && st_sum[st_head-1] == 0) st_head--;
            if (st_head>0)
                st_sum[st_head-1]--;
        }

    printf("%d\n", mx);
    return 0;
}

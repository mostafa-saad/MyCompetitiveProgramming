/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(k log k + n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define N 1000000

typedef struct pair {
    int first, second;
} pair;

pair make_pair(int st, int nd) {
    pair x;
    x.first = st;
    x.second = nd;
    return x;
}

int a[N + 1];
pair to_sort[N + 1];
int ans[N + 1];

int cmp(const void* _p1, const void* _p2) {
    const pair* p1 = _p1;
    const pair* p2 = _p2;
    if(p1->first < p2->first) return 1;
    if(p1->first > p2->first) return -1;
    if(p1->second < p2->second) return 1;
    if(p1->second > p2->second) return -1;
    return 0;
}

void swap(int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int main() {
    int k, p, q;
    int i;
    scanf("%d %d %d", &k, &p, &q);
    int n =0;

    for(i=1; i<=k; i++) {
        scanf("%d", &a[i]);
        n += a[i];
    }

    a[p] --;
    if(n > 1) a[q] --;

    if(a[p] < 0 || a[q] < 0) {
        puts("0");
        return 0;
    }

    for(i=1; i<=k; i++)
        to_sort[i] = make_pair(a[i], i);

    qsort(to_sort+1, k, sizeof(pair), cmp);

    ans[1] = p;
    ans[n] = q;

    int idx = 2;

    int x;

    for(i=1; i<=k; i++) {
        for(x=0; x < to_sort[i].first; x++) {
            ans[idx] = to_sort[i].second;
            idx += 2;
            if(idx >= n) idx = 3;
        }
    }

    for(i=2; i<=n-1 && ans[i-1] == ans[i]; i+=2) {
        swap(&ans[i], &ans[i+1]);
    }
    for(i=n-1; i>=3 && ans[i] == ans[i+1]; i-=2) {
        swap(&ans[i], &ans[i-1]);
    }

    for(i=1; i<n; i++) {
        if(ans[i] == ans[i+1]) {
            puts("0");
            return 0;
        }
    }
    for(i=1; i<=n; i++) {
        printf("%d ", ans[i]);
    }
    puts("");

    return 0;
}

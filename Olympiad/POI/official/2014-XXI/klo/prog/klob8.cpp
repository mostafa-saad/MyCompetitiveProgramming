/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Takie jak rozwiazanie wolne, lecz wykonuje    *
 *                         tylko log n petli na losowej permutacji       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1000000;

int a[N];
int ans[N];

int main() {
    int k, p, q;
    scanf("%d %d %d", &k, &p, &q);
    int n = 0;

    for(int i=1; i<=k; i++) {
        scanf("%d", a+i);
        n += a[i];
    }

    a[p] -- ;
    if( n > 1 ) a[q] --;
    ans[1] = p;
    ans[n] = q;

    if(a[p] < 0 || a[q] < 0) {
        puts("0");
        return 0;
    }

    int idx = 2;
    for(int i=1; i<=k; i++) {
        while(a[i]) {
            ans[idx++] = i;
            a[i]--;
        }
    }

    if(n > 1) random_shuffle(ans+2, ans+n);

    for(int j=1; j<=n; j*=2) {
        for(int i=2; i<=n-2; i++) {
            if(ans[i] == ans[i-1]) {
                swap(ans[i], ans[i+1]);
            }
        }
        for(int i=n-1; i>=3; i--) {
            if(ans[i] == ans[i+1])
                swap(ans[i], ans[i-1]);
        }
    }

    for(int i=2; i<=n; i++) {
        if(ans[i] == ans[i-1]) {
            puts("0");
            return 0;
        }
    }

    for(int i=1; i<=n; i++) printf("%d ", ans[i]);
    puts("");
}

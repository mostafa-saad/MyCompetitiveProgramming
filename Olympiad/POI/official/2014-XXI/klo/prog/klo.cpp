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

#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

const int N = 1000000;

int a[N + 1];
pair<int, int> to_sort[N + 1];
int ans[N + 1];

int main() {
    int k, p, q;
    ios_base::sync_with_stdio(0);
    cin >> k >> p >> q;

    for(int i=1; i<=k; i++) cin >> a[i];
    int n = accumulate(a+1, a+1+k, 0);

    a[p] --;
    if(n > 1) a[q] --;

    if(a[p] < 0 || a[q] < 0) {
        cout << "0" << endl;
        return 0;
    }

    for(int i=1; i<=k; i++)
        to_sort[i] = make_pair(a[i], i);

    sort(to_sort+1, to_sort+1+k, greater<pair<int, int> >());

    ans[1] = p;
    ans[n] = q;

    int idx = 2;

    for(int i=1; i<=k; i++) {
        for(int x=0; x < to_sort[i].first; x++) {
            ans[idx] = to_sort[i].second;
            idx += 2;
            if(idx >= n) idx = 3;
        }
    }

    for(int i=2; i<=n-1 && ans[i-1] == ans[i]; i+=2) {
        swap(ans[i], ans[i+1]);
    }
    for(int i=n-1; i>=3 && ans[i] == ans[i+1]; i-=2) {
        swap(ans[i], ans[i-1]);
    }

    for(int i=1; i<n; i++) {
        if(ans[i] == ans[i+1]) {
            cout << "0" << endl;
            return 0;
        }
    }
    for(int i=1; i<=n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

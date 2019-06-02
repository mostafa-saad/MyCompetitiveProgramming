/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Taksowki                                      *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <iostream>
using namespace std;

int n;
long long d, m, x[500000];

int main() {
    ios_base::sync_with_stdio(0);
    cin >> m >> d >> n;
    for (int i = 0; i < n; ++i)
        cin >> x[i];

    int best = -1;
    for (int i = 0; i < n; ++i)
        if (x[i] >= m - d && (best == -1 || x[best] > x[i]))
            best = i;
    if (best == -1) {
        cout << "0\n";
        return 0;
    }
    swap(x[best], x[n-1]);

    sort(x, x + n - 1);
    reverse(x, x + n - 1);

    for (int i = 0; i < n; ++i) {
        if (x[n-1] >= d + m || x[i] >= d + m) {
            cout << i + 1 << endl;
            return 0;
        }
        if (i == n - 1  || x[i] < d) {
            cout << "0\n";
            return 0;
        }
        long long delta = min(x[i] - d, d);
        d -= delta;
        m -= delta;
    }
}


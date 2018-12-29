/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

long long cross(long long x1, long long y1, long long x2, long long y2) {
    return x1 * y2 - x2 * y1;
}

long long dot(long long x1, long long y1, long long x2, long long y2) {
    return x1 * x2 + y1 * y2;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (cross(x1, y1, x2, y2) < 0) {
        swap(x1, x2);
        swap(y1, y2);
    }
    const bool angle0 = cross(x1, y1, x2, y2) == 0;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i];
    vector<int> k(n);
    for (int i = 0; i < n; ++i)
        cin >> k[i];
    vector<int> t(n);

    for (int i = 0; i < n; ++i) {
        if (t[i] != 0) continue;  // lampa zapalila sie wczesniej
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            t[u] = 1 + i;
            for (int v = 0; v < n; ++ v) {
                if (t[v] == 0 &&
                        cross(x1, y1, x[v]-x[u], y[v]-y[u]) >= 0 &&
                        cross(x[v]-x[u], y[v]-y[u], x2, y2) >= 0 &&
                        (!angle0 || dot(x[v]-x[u], y[v]-y[u], x1, y1) > 0)) {
                    --k[v];
                    if (k[v] == 0)
                        q.push(v);
                }
            }
        }
    }
    int dbg_count = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0)
            cout << " ";
        cout << t[i];
        if (t[i] < i + 1) ++dbg_count;
    }
    cout << endl;
    cerr << "n = " << n << ", lit by others = " << dbg_count << endl;
    return 0;
}

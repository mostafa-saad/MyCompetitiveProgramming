/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n log^2 n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Dziala tak jakby lampa zaczynala oswietlac    *
 *                         inne lampy dopiero po podlaczeniu do niej     *
 *                         pradu, nawet jesli zaswiecila sie wczesniej.  *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200 * 1000;

int n, result[MAXN];

struct Lamp {
    int x, y, k, id;
} lamps[MAXN];

void Distort(long long &x, long long& y) {
    long long m = max(max(x, -x), max(y, -y));
    long long d = (2 * 1000 * 1000 * 1000 + 2 + m - 1) / m;
    x *= d;
    y *= d;
    ++x;
}

void Input() {  // wczytywanie wejscia i przeksztalcenie ukladu wspolrzednych
    cin >> n;
    long long x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x1 * y2 == x2 * y1)
        Distort(x2, y2);
    if (x1 * y2 - x2 * y1 < 0) {
        swap(x1, x2);
        swap(y1, y2);
    }
    vector<long long> x(n), y(n);

    for (int i = 0; i < n; ++i) {
        long long a, b;
        cin >> a >> b;
        x[i] = x1 * b - y1 * a;
        y[i] = y2 * a - x2 * b;
    }

    vector<long long> temp;
    temp = x;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    for (int i = 0; i < n; ++i)
        lamps[i].x = lower_bound(temp.begin(), temp.end(), x[i]) - temp.begin();
    temp = y;
    sort(temp.begin(), temp.end());
    temp.erase(unique(temp.begin(), temp.end()), temp.end());
    for (int i = 0; i < n; ++i)
        lamps[i].y = lower_bound(temp.begin(), temp.end(), y[i]) - temp.begin();

    for (int i = 0; i < n; ++i)
        cin >> lamps[i].k;

    for (int i = 0; i < n; ++i)
        lamps[i].id = i;
}

bool Cmp(const Lamp& a, const Lamp& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int tree[MAXN];  // Fenwick tree

void TreeAdd(int key, int val) {
    while (key < n) {
        tree[key] += val;
        key |= (key + 1);
    }
}

int TreeQuery(int key) {
    int result = 0;
    while (key >= 0) {
        result += tree[key];
        key = (key & (key + 1)) - 1;
    }
    return result;
}

void Solve(int beg, int end, int min_result, int max_result) {
    if (beg == end) return;
    if (max_result - min_result == 1) {
        for (int i = beg; i < end; ++i)
            result[lamps[i].id] = min_result;
        return;
    }

    int mid_result = (min_result + max_result) / 2;
    // tego sortowania mozna by uniknac, gdyby partition ponizej bylo stabilne,
    // ale poniewaz i tak uzywamy potem drzewka, to nie zmienia to zloznosci
    sort(lamps + beg, lamps + end, Cmp);
    int mid = beg;
    for (int i = beg; i < end; ++i) {
        int temp = TreeQuery(lamps[i].y);
        if (lamps[i].id < mid_result || temp >= lamps[i].k) {
            if (lamps[i].id < mid_result)
                TreeAdd(lamps[i].y, 1);
            swap(lamps[i], lamps[mid++]);
        } else {
            lamps[i].k -= temp;
        }
    }
    for (int i = beg; i < mid; ++i)  // czyszczenie drzewka
        if (lamps[i].id < mid_result)
            TreeAdd(lamps[i].y, -1);

    Solve(beg, mid, min_result, mid_result);
    Solve(mid, end, mid_result, max_result);
}

void Output() {
    int dbg_count = 0;
    for (int i = 0; i < n; ++i) {
        if (i > 0)
            cout << " ";
        cout << 1 + result[i];
        if (result[i] < i) ++dbg_count;
    }
    cout << endl;
    cerr << "n = " << n << ", lit by others = " << dbg_count << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    Input();
    Solve(0, n, 0, n);
    Output();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const string CORRECT = "tocno";
const string WRONG_TRIANGULATION = "neispravna triangulacija";
const string WRONG_COLORING = "neispravno bojenje";

const int MAXN = 2e5 + 10;

int n;
pii nxt[MAXN];
pair<pii, int> diagonals[MAXN * 2];

int dist(int a, int b) {
    return (b + n - a) % n;
}

bool cmp(const pair<pii, int>& a, const pair<pii, int>& b) {
    return dist(a.fi.fi, a.fi.se) < dist(b.fi.fi, b.fi.se);
}

bool check_triangle(int a, int b, int c) {
    return a + b + c == 6 && a != b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    cin >> n;
    string colors;
    cin >> colors;
    for (int i = 0; i < n; i++) {
        nxt[i] = {(i + 1) % n, colors[i] - '0'};
    }

    for (int i = 0; i < n - 3; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;

        diagonals[2 * i] = {{a, b}, c};
        diagonals[2 * i + 1] = {{b, a}, c};
    }

    int m = 2 * (n - 3);
    sort(diagonals, diagonals + m, cmp);

    bool coloring = true;

    for (int i = 0; i < n - 2; i++) {
        int a = diagonals[i].fi.fi;
        int b = nxt[a].fi;
        int c = diagonals[i].fi.se;

        int color_a = nxt[a].se;
        int color_b = nxt[b].se;
        int color_c = diagonals[i].se;

        if (nxt[b].fi != c) {
            cout << WRONG_TRIANGULATION << "\n";
            return 0;
        }

        coloring &= check_triangle(color_a, color_b, color_c);

        nxt[a] = {c, color_c};
    }

    if (!coloring) {
        cout << WRONG_COLORING << "\n";
    } else {
        cout << CORRECT << "\n";
    }

    return 0;
}


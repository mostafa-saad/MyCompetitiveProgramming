#include <bits/stdc++.h>
using namespace std;

const int MaxN = 2e5 + 10;
int nxt[MaxN], color[MaxN], cnt[3];
int sol_x[MaxN], sol_y[MaxN], sol_c[MaxN];

int main() {
    int n;
    string s;
    cin >> n >> s;

    for (int i = 0; i < n; i++) {
        color[i] = s[i] - '1';
        cnt[s[i] - '1']++;
        nxt[i] = (i + 1) % n;
    }

    int x = 0;
    for (int i = 0; i < n - 3; i++) {
        if (max(cnt[0], max(cnt[1], cnt[2])) == n - i) {
            cout << "NE\n";
            return 0;
        }

        while (color[x] == color[nxt[x]] ||
               (cnt[color[x]] == 1 && cnt[color[nxt[x]]] == 1))
            x = nxt[x];

        int y = nxt[x];
        int new_color = 3 - color[x] - color[y];
        cnt[color[x]]--;
        cnt[color[y]]--;
        cnt[new_color]++;
        color[x] = new_color;
        nxt[x] = nxt[y];
        sol_x[i] = x;
        sol_y[i] = nxt[y];
        sol_c[i] = new_color;
    }

    if (cnt[0] == 1 && cnt[1] == 1) {
        cout << "DA\n";
        for (int i = 0; i < n - 3; i++)
            cout << sol_x[i] + 1 << " "
                 << sol_y[i] + 1 << " "
                 << sol_c[i] + 1 << "\n";
    } else {
        cout << "NE\n";
    }

    return 0;
}


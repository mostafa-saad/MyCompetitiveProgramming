#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

const int ALPHA = 26;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int sol_cnt = ALPHA, sol_l = -1, sol_r = -1;

    vector<int> last(ALPHA, -1), sorted(ALPHA + 1, -1);
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        sorted.erase(find(sorted.begin(), sorted.end(), last[c]));
        last[c] = i;
        sorted.insert(sorted.begin(), i);

        for (int j = 1; j <= ALPHA; j++)
            if (j * (sol_r - sol_l + 1) < sol_cnt * (i - sorted[j])) {
                sol_cnt = j;
                sol_l = sorted[j] + 1;
                sol_r = i;
            }
    }

    cout << sol_l + 1 << " " << sol_r + 1 << "\n";

    return 0;
}


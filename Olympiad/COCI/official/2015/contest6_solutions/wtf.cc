#include <iostream>
#include <algorithm>
using namespace std;

const int N = 3003;
int a[N][N];
int b[N][N];
int dp[N][N][3];

#define DOWN 0
#define LEFT 1
#define RIGHT 2
const int MINUS_INF = -1000 * 1000 * 1000;

int best(int i, int j) {
    return max(dp[i][j][DOWN],
            max(dp[i][j][LEFT], dp[i][j][RIGHT]));
}

int main () {
    int n, r;
    cin >> n >> r;
    for (int i = 0; i < n; ++i) {
        cin >> a[0][i];
        a[0][i] *= -1;
        int position = i;
        for (int j = 1; j < n; ++j) {
            position = (position + r) % n;
            a[j][position] = a[0][i];
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n - 1; ++j)
        {
            b[i][j] = a[i][j + 1] - a[i][j];

            for (int k = 0; k < 3; ++k)
                dp[i][j][k] = MINUS_INF;
        }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j)
        {
            dp[i][j][DOWN] = b[i][j] + (i > 0 ? best(i - 1, j) : 0);
            if (j > 0)
                dp[i][j][RIGHT] = b[i][j] +
                    max(dp[i][j - 1][DOWN], dp[i][j - 1][RIGHT]);
        }
        for (int j = n - 3; j >= 0; --j)
            dp[i][j][LEFT] = b[i][j] +
                max(dp[i][j + 1][DOWN], dp[i][j + 1][LEFT]);
    }

    int sol = MINUS_INF;
    for (int j = 0; j < n - 1; ++j)
        sol = max(sol, best(n - 1, j));
    cout << sol << endl;
}

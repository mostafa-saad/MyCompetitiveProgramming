#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 400;
const int INFV = 1001001001;

int N;
char S[MAXN + 1]; int A[MAXN];
int dp[MAXN + 1][MAXN + 1][MAXN + 1][3];
int cnts[3], locs[3][MAXN], prevs[3][MAXN];

void chmin(int& x, int y)
{
    x = min(x, y);
}

int main()
{
    scanf("%d%s", &N, S);

    for (int i = 0; i < N; ++i) {
        switch (S[i]) {
            case 'R': A[i] = 0; break;
            case 'G': A[i] = 1; break;
            case 'Y': A[i] = 2; break;
        }
    }

    for (int i = 0; i < 3; ++i) cnts[i] = 0;
    for (int i = 0; i < N; ++i) {
        locs[A[i]][cnts[A[i]]++] = i;
        for (int j = 0; j < 3; ++j) prevs[j][i] = cnts[j];
    }

    for (int a = 0; a <= cnts[0]; ++a) {
        for (int b = 0; b <= cnts[1]; ++b) {
            for (int c = 0; c <= cnts[2]; ++c) {
                for (int s = 0; s < 3; ++s) {
                    dp[a][b][c][s] = INFV;
                }
            }
        }
    }

    dp[0][0][0][0] = dp[0][0][0][1] = dp[0][0][0][2] = 0;

    for (int a = 0; a <= cnts[0]; ++a) {
        for (int b = 0; b <= cnts[1]; ++b) {
            for (int c = 0; c <= cnts[2]; ++c) {
                for (int s = 0; s < 3; ++s) {
                    if (s != 0 && a < cnts[0]) {
                        int p = locs[0][a];
                        chmin(dp[a + 1][b][c][0], dp[a][b][c][s] + max(0, prevs[1][p] - b) + max(0, prevs[2][p] - c));
                    }
                    if (s != 1 && b < cnts[1]) {
                        int p = locs[1][b];
                        chmin(dp[a][b + 1][c][1], dp[a][b][c][s] + max(0, prevs[0][p] - a) + max(0, prevs[2][p] - c));
                    }
                    if (s != 2 && c < cnts[2]) {
                        int p = locs[2][c];
                        chmin(dp[a][b][c + 1][2], dp[a][b][c][s] + max(0, prevs[0][p] - a) + max(0, prevs[1][p] - b));
                    }
                }
            }
        }
    }

    int ret = min({ dp[cnts[0]][cnts[1]][cnts[2]][0], dp[cnts[0]][cnts[1]][cnts[2]][1], dp[cnts[0]][cnts[1]][cnts[2]][2] });
    if (ret >= INFV) ret = -1;
    printf("%d\n", ret);

    return 0;
}

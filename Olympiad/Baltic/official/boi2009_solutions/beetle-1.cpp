/* A solution for BOI 2009 task BEETLE.
 * Correct. Requires O(N^3) time and O(N^2) memory.
 * Author: Linas Petrauskas
 */

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

    const int MAXN = 300, MAXM = 1000000, INFINITY = MAXN*MAXM;

    int x[MAXN + 1];
    int L[2][MAXN + 1][MAXN + 1] = { 0 };
    int R[2][MAXN + 1][MAXN + 1] = { 0 }; 

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> x[i];

    x[n++] = 0;
    sort(x, x + n);

    int s = 0;
    while (x[s])
        s++;

    int answer = 0, curr = 0, prev;

    for (int k = 1; k < n; k++) {
        prev = curr;
        curr = (curr + 1) % 2;

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++) 
            {
                L[curr][i][j] = R[curr][i][j] = INFINITY;
                if (n - (j - i + 1) >= k) {
                    if (i > 0) {
                        L[curr][i][j] = min(L[curr][i][j], L[prev][i - 1][j] + k * (x[i] - x[i - 1]));
                        R[curr][i][j] = min(R[curr][i][j], L[prev][i - 1][j] + k * (x[j] - x[i - 1]));
                    }
                    if (j < n - 1) {
                        L[curr][i][j] = min(L[curr][i][j], R[prev][i][j + 1] + k * (x[j + 1] - x[i]));
                        R[curr][i][j] = min(R[curr][i][j], R[prev][i][j + 1] + k * (x[j + 1] - x[j]));
                    }
                }
            }

        if (answer < k * m - L[curr][s][s])
            answer = k * m - L[curr][s][s];
    }

    cout << answer << endl;

    return 0;
}

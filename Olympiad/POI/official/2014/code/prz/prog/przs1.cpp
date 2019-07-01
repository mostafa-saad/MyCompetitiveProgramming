/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Przestepcy                                    *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 1000001;
const int MAX_K = 1000001;

int N, K, t[MAX_N], col[2][MAX_K], s[2], p[2] = {0, 0}, finalRes[2] = {MAX_N, 0};
vector<int> solution;

int main() {
    int ret;

    ret = scanf("%d%d", &N, &K);

    for (int i = 0; i < N; i++) {
        ret = scanf("%d", &t[i]);
        t[i]--;
    }

    ret = scanf("%d%d", &s[0], &s[1]);

    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= s[i]; j++) {
            ret = scanf("%d", &col[i][j]);
            col[i][j]--;
        }

    for (int i = 0; i < K; i++) {
        bool ok;

        col[0][0] = i;
        col[1][0] = i;
        p[0] = 0;
        p[1] = 0;

        ok = false;
        for (int k = 0; k < N; k++) {
            if ((p[0] <= s[0]) && (col[0][p[0]] == t[k]))
                p[0]++;
            if (p[0] == s[0]+1) {
                p[0] = k;
                ok = true;
                break;
            }
        }
        if (!ok)
            p[0] = N;

        ok = false;
        for (int k = N-1; k >= 0; k--) {
            if ((p[1] <= s[1]) && (col[1][p[1]] == t[k]))
                p[1]++;
            if (p[1] == s[1]+1) {
                p[1] = k;
                ok = true;
                break;
            }
        }
        if (!ok)
            p[1] = 0;

        if (p[0] <= p[1]) {
            finalRes[0] = min(finalRes[0], p[0]);
            finalRes[1] = max(finalRes[1], p[1]);
        }
    }

    if (ret < 0) return 0;

    for (int j = finalRes[0]; j <= finalRes[1]; j++)
        if (t[j] == col[0][s[0]])
            solution.push_back(j);

    printf("%d\n", (int)solution.size());
    for (int i = 0; i < (int)solution.size(); i++)
        printf("%d ", solution[i]+1);
    printf("\n");

    return 0;
}

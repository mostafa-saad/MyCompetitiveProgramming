/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Przestepcy                                    *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 1000001;
const int MAX_K = 1000001;

int N, K, t[MAX_N], pos[MAX_K], col[MAX_N], nast[MAX_N], seq[MAX_N], f[2][MAX_N], result[2][MAX_K], s[2], finalRes[2];
vector<int> solution;

int main() {
    int ret;

    ret = scanf("%d%d", &N, &K);

    for (int i = 0; i < N; i++) {
        ret = scanf("%d", &t[i]);
        t[i]--;
    }

    ret = scanf("%d%d", &s[0], &s[1]);

    for (int i = 0; i < 2; i++) {
        int curPos = 0;

        fill(pos, pos+K, N);
        for (int j = N-1; j >= 0; j--) {
            nast[j] = pos[t[j]];
            pos[t[j]] = j;
        }

        for (int j = 1; j <= s[i]; j++) {
            ret = scanf("%d", &col[j]);
            col[j]--;
        }

        if (ret < 0) return 0;

        for (int j = 1; j <= s[i]; j++) {
            while ((pos[col[j]] < curPos) && (pos[col[j]] < N))
                pos[col[j]] = nast[pos[col[j]]];
            curPos = pos[col[j]];
            seq[j] = curPos;
        }

        for (int j = 0; j < N; j++) {
            int curPos = 0;

            seq[0] = j;

            while ((curPos <= s[i]) && (seq[curPos] >= seq[curPos+1])) {
                while ((seq[curPos] >= seq[curPos+1]) && (seq[curPos+1] < N))
                    seq[curPos+1] = nast[seq[curPos+1]];
                curPos++;
            }

            f[i][j] = seq[s[i]];
        }

        if (i == 0) {
            fill(result[0], result[0]+N, N);
            for (int j = 0; j < N; j++)
                result[0][t[j]] = min(result[0][t[j]], f[0][j]);
        }
        if (i == 1) {
            for (int j = 0; j < N; j++)
                result[1][t[j]] = max(result[1][t[j]], N-1-f[1][j]);
        }

        reverse(t, t+N);
    }

    finalRes[0] = N;
    for (int i = 0; i < K; i++)
        if (result[0][i] <= result[1][i]) {
            finalRes[0] = min(finalRes[0], result[0][i]);
            finalRes[1] = max(finalRes[1], result[1][i]);
        }

    for (int j = finalRes[0]; j <= finalRes[1]; j++)
        if (t[j] == col[s[1]])
            solution.push_back(j);


    printf("%d\n", (int)solution.size());
    for (int i = 0; i < (int)solution.size(); i++)
        printf("%d ", solution[i]+1);
    printf("\n");

    return 0;
}

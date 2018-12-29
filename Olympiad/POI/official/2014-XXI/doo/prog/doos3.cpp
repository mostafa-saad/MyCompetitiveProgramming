/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(sn log n)                                   *
 *   Zlozonosc pamieciowa: O(n log n)                                    *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int MAXLOG = 18;

int n, q, t[MAXN], prefSum[MAXN], edge[MAXN], jump[MAXLOG][MAXN], maxLength = 0;

void ReadData() {
    scanf("%d%d", &n, &q);
    if (n > 100000) for (;;);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
        maxLength = max(maxLength, t[i]);
    }
}

void ComputePrefixSums() {
    prefSum[0] = 0;
    for (int i = 1; i <= n; i++)
        prefSum[i] = prefSum[i-1]+t[i-1];
}

int Distance(int from, int to) {
    return (from < to ? prefSum[to]-prefSum[from] : prefSum[n]+prefSum[to]-prefSum[from]);
}

void ComputeEdges(int maxD) {
    int pos = 0;
    for (int i = 0; i < n; i++) {
        while (Distance(i, (pos+1)%n) <= maxD) pos = (pos+1)%n;
        edge[i] = pos;
    }
}

void ComputeNextEdges() {
    for (int i = 0; i < n; i++) jump[0][i] = (i < edge[i] ? edge[i]-i : n+edge[i]-i);
    for (int i = 1; i < MAXLOG; i++)
        for (int j = 0; j < n; j++) {
            jump[i][j] = jump[i-1][j]+jump[i-1][(j+jump[i-1][j])%n];
            if (jump[i][j] > n) jump[i][j] = n;
        }
}

int PathLength(int from) {
    int u = from, sumJump = 0, result = 0;
    for (int i = MAXLOG-1; i >= 0; i--) {
        if (sumJump+jump[i][u] < n) {
            result += 1<<i;
            sumJump += jump[i][u];
            u = (u+jump[i][u])%n;
        }
    }
    return result+1;
}

int Solve(int maxD) {
    int result = MAXN;
    for (int i = 0; i < n; i++)
        result = min(result, PathLength(i));
    return result;
}

int main() {
    ReadData();
    ComputePrefixSums();

    while (q--) {
        int x, result;
        scanf("%d", &x);
        if (maxLength > x) {
            printf("NIE\n");
            continue;
        }
        if (x >= prefSum[n]) {
            printf("1\n");
            continue;
        }
        ComputeEdges(x);
        ComputeNextEdges();
        result = Solve(x);
        printf("%d\n", result);
    }

    return 0;
}

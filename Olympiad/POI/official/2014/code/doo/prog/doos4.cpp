/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Dookola swiata                                *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;

int n, q, t[MAXN], prefSum[MAXN], edge[MAXN], maxLength = 0;

void ReadData() {
    scanf("%d%d", &n, &q);
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

int PathLength(int from) {
    int result = 0, u = from, distancePassed = 0;
    while (distancePassed < prefSum[n]) {
        distancePassed += Distance(u, edge[u]);
        u = edge[u];
        result++;
    }
    return result;
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
        result = Solve(x);
        printf("%d\n", result);
    }

    return 0;
}

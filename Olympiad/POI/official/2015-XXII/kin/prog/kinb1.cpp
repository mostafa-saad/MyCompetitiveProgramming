/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kinoman                                            *
 *   Autor programu:       Karol Pokorski/kpok/pokorski                       *
 *   Zlozonosc czasowa:    O((n+m) log n)                                     *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/



#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000005;
const int TREE_SIZE = 1048576;

int seq[MAXN], val[MAXN], nextSame[MAXN], ptrElem[MAXN], occurCnt[MAXN], treeSum[2*TREE_SIZE], treeMax[2*TREE_SIZE];

void TreeUpdate(int from, int to, int change) {
    int idxFrom = from+TREE_SIZE, idxTo = to+TREE_SIZE;

    if (from > to) return;

    treeSum[idxFrom] += change;
    treeMax[idxFrom] += change;
    if (idxFrom != idxTo) {
        treeSum[idxTo] += change;
        treeMax[idxTo] += change;
    }

    while (idxFrom / 2 != idxTo / 2) {
        if (idxFrom % 2 == 0) {
            treeSum[idxFrom+1] += change;
            treeMax[idxFrom+1] += change;
        }
        if (idxTo % 2 == 1) {
            treeSum[idxTo-1] += change;
            treeMax[idxTo-1] += change;
        }

        idxFrom /= 2;
        idxTo /= 2;

        treeMax[idxFrom] = max(treeMax[2*idxFrom], treeMax[2*idxFrom+1]) + treeSum[idxFrom];
        treeMax[idxTo] = max(treeMax[2*idxTo], treeMax[2*idxTo+1]) + treeSum[idxTo];
    }

    while (idxFrom != 1) {
        idxFrom /= 2;
        treeMax[idxFrom] = max(treeMax[2*idxFrom], treeMax[2*idxFrom+1]) + treeSum[idxFrom];
    }
}

int TreeMax(int from, int to) {
    int idxFrom = from+TREE_SIZE, idxTo = to+TREE_SIZE, result = 0, fromResult = treeMax[idxFrom], toResult = treeMax[idxTo];

    while (idxFrom / 2 != idxTo / 2) {
        if (idxFrom % 2 == 0)
            fromResult = max(fromResult, treeMax[idxFrom+1]);
        if (idxTo % 2 == 1)
            toResult = max(toResult, treeMax[idxTo-1]);

        idxFrom /= 2;
        idxTo /= 2;

        fromResult += treeSum[idxFrom];
        toResult += treeSum[idxTo];
    }

    result = max(fromResult, toResult);

    while (idxFrom != 1) {
        idxFrom /= 2;
        result += treeSum[idxFrom];
    }

    return result;
}

int main() {
    int n, m, curResult = 0, maxResult = 0;

    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &seq[i]);
        seq[i]--;
    }

    for (int i = 0; i < m; i++)
        scanf("%d", &val[i]);

    fill(ptrElem, ptrElem+m, n);
    nextSame[n] = n;
    for (int i = n-1; i >= 0; i--) {
        nextSame[i] = ptrElem[seq[i]];
        ptrElem[seq[i]] = i;
    }

    for (int i = 0; i < n; i++) {
        if (occurCnt[seq[i]] == 0)
            curResult += val[seq[i]];
        if (occurCnt[seq[i]] == 1)
            curResult -= val[seq[i]];
        occurCnt[seq[i]]++;

        TreeUpdate(i, i, curResult);
    }

    maxResult = TreeMax(0, n-1);

    for (int i = 0; i < n; i++) {
        TreeUpdate(i, nextSame[i]-1, -val[seq[i]]);
        TreeUpdate(nextSame[i], nextSame[nextSame[i]]-1, +val[seq[i]]);
        maxResult = max(maxResult, TreeMax(0, n-1));
    }

    printf("%d\n", maxResult);

    return 0;
}

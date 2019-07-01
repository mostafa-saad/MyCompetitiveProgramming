/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kinoman                                            *
 *   Autor programu:       Karol Pokorski/kpok/pokorski                       *
 *   Zlozonosc czasowa:    O((n+m) sqrt(n))                                   *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie prawie wzorcowe,                       *
 *                         pierwiastkowa struktura zamiast drzewa             *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int LL;

const int MAXN = 1000005;
const int BUCKET_SIZE = 1000;
const int BUCKETS_CNT = MAXN / BUCKET_SIZE + 5;

int seq[MAXN], val[MAXN], nextSame[MAXN], ptrElem[MAXN], occurCnt[MAXN];
LL fullRange[BUCKETS_CNT], onlyRange[MAXN], maxRange[BUCKETS_CNT];

void TreeUpdate(int from, int to, LL change) {
    if (from > to)
        return;

    int fromBucket = from / BUCKET_SIZE, toBucket = to / BUCKET_SIZE;

    for (int i = from; i <= min(to, (fromBucket+1)*BUCKET_SIZE-1); i++) onlyRange[i] += change;
    maxRange[fromBucket] = 0;
    for (int i = fromBucket * BUCKET_SIZE; i < (fromBucket+1) * BUCKET_SIZE; i++)
        maxRange[fromBucket] = max(maxRange[fromBucket], fullRange[fromBucket] + onlyRange[i]);

    for (int i = fromBucket+1; i < toBucket; i++) {
        fullRange[i] += change;
        maxRange[i] += change;
    }

    if (fromBucket != toBucket) {
        for (int i = max(from, toBucket*BUCKET_SIZE); i <= to; i++) onlyRange[i] += change;
        maxRange[toBucket] = 0;
        for (int i = toBucket * BUCKET_SIZE; i < (toBucket+1) * BUCKET_SIZE; i++)
            maxRange[toBucket] = max(maxRange[toBucket], fullRange[toBucket] + onlyRange[i]);
    }
}

LL TreeMax(int from, int to) {
    int fromBucket = from / BUCKET_SIZE, toBucket = to / BUCKET_SIZE;
    LL result = 0LL;

    for (int i = from; i <= min(to, (fromBucket+1)*BUCKET_SIZE-1); i++)
        result = max(result, onlyRange[i] + fullRange[fromBucket]);

    for (int i = fromBucket+1; i < toBucket; i++)
        result = max(result, maxRange[i]);

    if (fromBucket != toBucket) {
        for (int i = max(from, toBucket*BUCKET_SIZE); i <= to; i++)
            result = max(result, onlyRange[i] + fullRange[toBucket]);
    }

    return result;
}

int main() {
    int n, m;
    LL curResult = 0LL, maxResult = 0LL;

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

    printf("%Ld\n", maxResult);

    return 0;
}

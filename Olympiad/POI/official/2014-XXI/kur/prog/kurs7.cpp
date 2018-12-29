/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O((n+m) sqrt n)                               *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Rozwiazanie prawie wzorcowe, z tym, ze        *
 *                         zamiast drzewa przedzialowego jest            *
 *                         pierwiastkowa struktura kubelkowa.            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define F first
#define S second

const int MAXN = 524288;
const int SQRT = 725;

int t[MAXN], eq[2*MAXN], gcand[SQRT], ghand[SQRT], qcand[MAXN], res[MAXN], curSum[MAXN], q[MAXN][2];

inline bool CmpEQ(int a, int b) {
    int qa = q[a/2][a%2], qb = q[b/2][b%2];
    if (qa != qb) return qa < qb;
    if (a%2 != b%2) return a%2 < b%2;
    return a < b;
}

inline pair<int,int> MergeLead(pair<int,int> a, pair<int,int> b) {
    if (a.F == b.F) return make_pair(a.F, a.S+b.S);
    if (a.S < b.S) swap(a, b);
    return make_pair(a.F, a.S-b.S);
}

int GetCand(int from, int to) {
    int pos;
    pair<int,int> curRes = make_pair(-1, 0);
    for (pos = from; (pos <= to && pos%SQRT != 0); pos++) curRes = MergeLead(curRes, make_pair(t[pos], 1));
    for (; pos < (to/SQRT)*SQRT; pos+=SQRT) curRes = MergeLead(curRes, make_pair(gcand[pos/SQRT], ghand[pos/SQRT]));
    for (; pos <= to; pos++) curRes = MergeLead(curRes, make_pair(t[pos], 1));
    return curRes.F;
}

int main() {
    int n, m, pos = 0;

    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
        t[i]--;
    }
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &q[i][0], &q[i][1]);
        q[i][0]--;
        q[i][1]--;
        eq[2*i] = 2*i;
        eq[2*i+1] = 2*i+1;
    }

    sort(eq, eq+2*m, CmpEQ);

    for (int i = 0; i < SQRT; i++) {
        gcand[i] = -1;
        ghand[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        pair<int,int> mergeRes = MergeLead(make_pair(gcand[i/SQRT], ghand[i/SQRT]), make_pair(t[i], 1));
        gcand[i/SQRT] = mergeRes.F;
        ghand[i/SQRT] = mergeRes.S;
    }

    for (int i = 0; i < m; i++) qcand[i] = GetCand(q[i][0], q[i][1]);

    for (int i = 0; i < 2*m; i++) {
        while ((pos < n) && (pos < q[eq[i]/2][eq[i]%2])) {
            curSum[t[pos]]++;
            pos++;
        }
        if ((pos <= q[eq[i]/2][eq[i]%2]) && (eq[i]%2 == 1)) {
            curSum[t[pos]]++;
            pos++;
        }
        if (eq[i]%2 == 0) res[eq[i]/2] = -curSum[qcand[eq[i]/2]];
        else res[eq[i]/2] += curSum[qcand[eq[i]/2]];
    }

    for (int i = 0; i < m; i++)
        if (res[i] > (q[i][1]-q[i][0]+1)/2) printf("%d\n", qcand[i]+1);
        else printf("0\n");

    return 0;
}

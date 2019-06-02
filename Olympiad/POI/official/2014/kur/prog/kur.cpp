/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O((n+m) log n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define F first
#define S second

const int MAXN = 524288;

int t[MAXN], eq[2*MAXN], cand[2*MAXN], hand[2*MAXN], qcand[MAXN], res[MAXN], curSum[MAXN], q[MAXN][2];

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
    pair<int,int> curRes = make_pair(-1, 0);
    from += MAXN;
    to += MAXN;
    curRes = MergeLead(curRes, make_pair(cand[from], hand[from]));
    if (from != to) curRes = MergeLead(curRes, make_pair(cand[to], hand[to]));

    while (from/2 != to/2) {
        if (from%2 == 0) curRes = MergeLead(curRes, make_pair(cand[from+1], hand[from+1]));
        if (to%2 == 1) curRes = MergeLead(curRes, make_pair(cand[to-1], hand[to-1]));
        from /= 2;
        to /= 2;
    }

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

    for (int i = 0; i < MAXN; i++) {
        if (i < n) {
            cand[MAXN+i] = t[i];
            hand[MAXN+i] = 1;
        }
        else {
            cand[MAXN+i] = -1;
            hand[MAXN+i] = 0;
        }
        cand[i] = -1;
        hand[i] = 0;
    }
    for (int i = MAXN-1; i >= 1; i--) {
        pair<int,int> mergeRes = MergeLead(make_pair(cand[2*i], hand[2*i]), make_pair(cand[2*i+1], hand[2*i+1]));
        cand[i] = mergeRes.F;
        hand[i] = mergeRes.S;
    }

    for (int i = 0; i < m; i++) qcand[i] = GetCand(q[i][0], q[i][1]);

    for (int i = 0; i < 2*m; i++) {
        while ((pos < n) && (pos < q[eq[i]/2][eq[i]%2])) {
            curSum[t[pos]]++;
            pos++;
        }
        if ((eq[i]%2 == 1) && (pos == q[eq[i]/2][eq[i]%2])) {
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

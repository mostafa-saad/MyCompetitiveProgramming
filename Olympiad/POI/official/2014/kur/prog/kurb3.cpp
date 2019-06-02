/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Rozwiazanie alternatywne, lecz dokonuje za    *
 *                         malo sprawdzen.                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define F first
#define S second

const int MAXN = 524288;
const int NUM_CHECK = 21;

int t[MAXN], eq[2*MAXN], qcand[MAXN][2], res[MAXN][2], curSum[MAXN], q[MAXN][2], temp[MAXN], temp2[NUM_CHECK];

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

pair<int,int> GetCand(int from, int to) {
    int tempCount = 0, maxX[2] = {-1, -1}, maxC[2] = {-1, -1};
    for (int i = 0; i < NUM_CHECK; i++) {
        int x = t[rand()%(to-from+1)+from];
        temp[x]++;
        if (temp[x] == 1) {
            temp2[tempCount] = x;
            tempCount++;
        }
    }
    for (int i = 0; i < tempCount; i++) {
        int x = temp2[i];
        if (temp[x] > maxC[0]) {
            maxX[1] = maxX[0];
            maxC[1] = maxC[0];
            maxX[0] = x;
            maxC[0] = temp[x];
        }
        else if (temp[x] > maxC[1]) {
            maxX[1] = x;
            maxC[1] = temp[x];
        }
    }
    for (int i = 0; i < tempCount; i++) {
        temp[temp2[i]] = 0;
        temp2[i] = 0;
    }
    if (maxX[1] == -1) maxX[1] = maxX[0];
    return make_pair(maxX[0], maxX[1]);
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

    for (int i = 0; i < m; i++) {
        pair<int,int> cand = GetCand(q[i][0], q[i][1]);
        qcand[i][0] = cand.F;
        qcand[i][1] = cand.S;
    }

    for (int i = 0; i < 2*m; i++) {
        while ((pos < n) && (pos < q[eq[i]/2][eq[i]%2])) {
            curSum[t[pos]]++;
            pos++;
        }
        if ((pos == q[eq[i]/2][eq[i]%2]) && (eq[i]%2 == 1)) {
            curSum[t[pos]]++;
            pos++;
        }
        for (int j = 0; j < 2; j++) {
            if (eq[i]%2 == 0) res[eq[i]/2][j] = -curSum[qcand[eq[i]/2][j]];
            else res[eq[i]/2][j] += curSum[qcand[eq[i]/2][j]];
        }
    }

    for (int i = 0; i < m; i++) {
        if (res[i][0] > (q[i][1]-q[i][0]+1)/2) printf("%d\n", qcand[i][0]+1);
        else if (res[i][1] > (q[i][1]-q[i][0]+1)/2) printf("%d\n", qcand[i][1]+1);
        else printf("0\n");
    }

    return 0;
}

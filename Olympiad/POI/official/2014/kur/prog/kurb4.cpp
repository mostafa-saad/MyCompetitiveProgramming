/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Jak rozwiazanie wzorcowe, tylko ze znajduje   *
 *                         jednego kandydata na lidera, a nie dwoch.     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

#define F first
#define S second

const int MAXN = 524288;
const int NUM_CHECK = 101;

int t[MAXN], eq[2*MAXN], qcand[MAXN], res[MAXN], curSum[MAXN], q[MAXN][2], temp[MAXN], temp2[NUM_CHECK];

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
    int tempCount = 0, maxX = -1, maxC = -1;
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
        if (temp[x] > maxC) {
            maxX = x;
            maxC = temp[x];
        }
    }
    for (int i = 0; i < tempCount; i++) {
        temp[temp2[i]] = 0;
        temp2[i] = 0;
    }
    return maxX;
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

    for (int i = 0; i < m; i++) qcand[i] = GetCand(q[i][0], q[i][1]);

    for (int i = 0; i < 2*m; i++) {
        while ((pos < n) && (pos < q[eq[i]/2][eq[i]%2])) {
            curSum[t[pos]]++;
            pos++;
        }
        if ((pos == q[eq[i]/2][eq[i]%2]) && (eq[i]%2 == 1)) {
            curSum[t[pos]]++;
            pos++;
        }
        if (eq[i]%2 == 0) res[eq[i]/2] = -curSum[qcand[eq[i]/2]];
        else res[eq[i]/2] += curSum[qcand[eq[i]/2]];
    }

    for (int i = 0; i < m; i++) {
        if (res[i] > (q[i][1]-q[i][0]+1)/2) printf("%d\n", qcand[i]+1);
        else printf("0\n");
    }

    return 0;
}

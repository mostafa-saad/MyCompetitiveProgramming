/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Podobne do rozwiazania O(n log^2 n), ale bez  *
 *                         wyszukiwania binarnego.                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1000*1000;
const int MM = (1<<21);

char s[N];
int n;

/* Drzewo przedzialowe - minimalny sufiks na przedziale */

int M;
int sum[MM], mnsuf[MM];

void initTree();
void insert(int x, int val);
int mnsuf_query(int a, int b);

/* Rozwiazanie */

int st_sum[N], st_jump[N]; // stos
int st_head = 0;

void preprocess() {
    initTree();
    for (int i = 0; i < n; ++i)
        insert(i, s[i] == 'p' ? 1 : -1);
}

int max_left_jump(int k) {
//    printf("stack:");
//    for(int i = 0; i < st_head; ++i)
//        printf(" %d", st_jump[i]);
//    printf(" <- %d\n", k);
    for(int i = 0; i < st_head; ++i) {
        if (mnsuf_query(st_jump[i], k) >= 0)
            return k - st_jump[i] + 1;
    }
    return 0;
}

int main() {
    int mx = 0;
    scanf("%d%s", &n, s);
    preprocess();

    for (int i = 0; i < n; ++i)
        if (s[i] == 'p') {
            st_jump[st_head] = i;
            st_sum[st_head] = 1;
            st_head++;
            mx = max(mx, max_left_jump(i));
        } else {
            while (st_head>0 && st_sum[st_head-1] == 0) st_head--;
            if (st_head>0)
                st_sum[st_head-1]--;
        }

    printf("%d\n", mx);
    return 0;
}

/* Implementacja metod drzewa przedzialowego */

void initTree() {
    M = 1;
    while (n >= M) M <<= 1;
}

void insert(int x, int val) {
    int v = M + x, ls, rs;

    sum[v] = mnsuf[v] = val;
    while (v != 1) {
        v >>= 1;
        ls = v<<1, rs = ls+1;
        sum[v] = sum[ls] + sum[rs];
        mnsuf[v] = min(mnsuf[rs], sum[rs]+mnsuf[ls]);
    }
}

int mnsuf_query(int a, int b) {
    int va = M+a, vb = M+b;
    int mnsufA, sumA, mnsufB, sumB;
    mnsufA = sumA = sum[va], mnsufB = sumB = sum[vb];
    while ((va>>1) != (vb>>1)) {
//        printf("(%d,%d), (%d,%d)\n", mnsufA, sumA, mnsufB, sumB);
        if ((va&1) == 0) {
            mnsufA = min(mnsufA+sum[va+1], mnsuf[va+1]);
            sumA += sum[va+1];
        }
        if ((vb&1) == 1) {
            mnsufB = min(mnsufB, mnsuf[vb-1]+sumB);
            sumB += sum[vb-1];
        }
        va >>= 1, vb >>= 1;
    }
//    printf("(%d,%d), (%d,%d)\n", mnsufA, sumA, mnsufB, sumB);
    if (a != b)
        return min(mnsufB, mnsufA + sumB);
    else
        return mnsufB;
}

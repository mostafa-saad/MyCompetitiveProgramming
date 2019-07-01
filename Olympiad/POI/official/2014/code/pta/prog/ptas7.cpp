/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(qn log n)                                   *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1048576;
const int INF = 1000000001;

int T[MAXN], tree[2*MAXN];
pair<int,int> st[MAXN];

void TreeUpdate(int x, int y) {
    x += MAXN;
    tree[x] = y;

    while (x > 0) {
        x /= 2;
        tree[x] = min(tree[2*x], tree[2*x+1]);
    }
}

int TreeFind(int x) {
    int result = INF;

    x += MAXN;
    result = tree[x];

    while (x > 0) {
        if (x%2 == 0)
            result = min(result, tree[x+1]);
        x /= 2;
    }

    return result;
}

int main() {
    int n, k, q, curRes = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
        st[i] = make_pair(T[i], i);
    }
    sort(&st[0], &st[n]);
    for (int i = 0; i < n; i++)
        T[st[i].second] = i;

    fill(tree, tree+2*MAXN, INF);

    scanf("%d", &q);

    while (q--) {
        scanf("%d", &k);

        TreeUpdate(T[0], 0);

        for (int i = 1; i < n; i++) {
            if (i > k)
                TreeUpdate(T[i-k-1], INF);
            curRes = min(TreeFind(T[i]+1), TreeFind(0)+1);
            TreeUpdate(T[i], curRes);
        }

        for (int i = 0; i <= n+1; i++)
            TreeUpdate(i, INF);

        printf("%d\n", curRes);
    }

    return 0;
}

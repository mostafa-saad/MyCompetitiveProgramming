/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Jan Kanty Milczek                             *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         std::set zamiast drzew przedzialowych         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#define F first
#define S second
#define MP make_pair
#define FOREACH(_i, _c) for (__typeof((_c).begin()) _i = (_c).begin(); _i != (_c).end(); ++_i)
#define scanf(Args...) (scanf(Args)?:0)
using namespace std;

typedef pair<int, int> PII;
const int MaxN = 500000;

vector<int> outE[MaxN + 2], inE[MaxN + 2];
int n, m, incoming[MaxN + 2], topoOrd[MaxN + 2], upTo[MaxN + 2], from[MaxN + 2], resultV, resultL = MaxN;

int len(PII x) {
    return upTo[x.F] + from[x.S] - 1;
}
struct cmp {
    bool operator () (PII x, PII y) {
        if (len(x) == len(y))
            return x < y;
        return len(x) > len(y);
    }
};

set<pair<int, int>, cmp> above;

void addEdge(int w1, int w2) {
    outE[w1].push_back(w2);
    inE[w2].push_back(w1);
    incoming[w2]++;
}

void licz(int *what, vector<int> *kr) {
    for (int i = 0; i <= n; ++i) {
        int cu = topoOrd[i];
        FOREACH(it, kr[cu])
        if (what[*it] < what[cu] + 1)
            what[*it] = what[cu] + 1;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        addEdge(0, i);
        addEdge(i, n + 1);
    }

    n += 2;

    for (int i = 0; i < m; ++i) {
        int w1, w2;
        scanf("%d%d", &w1, &w2);
        addEdge(w1, w2);
    }

    /* Order */ {
        int sz = 1;
        for (int i = 0; i < sz; ++i) {
            FOREACH(it, outE[topoOrd[i]]) {
                --incoming[*it];
                if (incoming[*it] == 0)
                    topoOrd[sz++] = *it;
            }
        }
    }

    licz(upTo, outE);
    reverse(topoOrd, topoOrd + n);
    licz(from, inE);
    reverse(topoOrd, topoOrd + n);

    for (int i = 1; i < n - 1; ++i) {
        int pr = topoOrd[i - 1], cu = topoOrd[i];
        FOREACH(it, outE[pr])
        above.insert(MP(pr, *it));
        FOREACH(it, inE[cu])
        above.erase(MP(*it, cu));
        if (resultL > len(*above.begin())) {
            resultL = len(*above.begin());
            resultV = cu;
        }
    }
    printf("%d %d\n", resultV, resultL);
}


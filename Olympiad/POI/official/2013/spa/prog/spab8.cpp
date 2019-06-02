/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Miroslaw Michalski                            *
 *   Zlozonosc czasowa:    O(n^2 * k)                                    *
 *   Zlozonosc pamieciowa: O(nk)                                         *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Pamieciozerny DFS                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>

using std::set;
using std::vector;

const int MAXN = 123;

int k, n, visited, limit;
long long nodeA, nodeB, destination;
set<long long> s, used;
bool decisionOverflow, decisionFound;

long long translate(char* c) {
    long long res = 0;
    for (int i = 0; i < k; ++i) {
        if (c[i] == '1') {
            res += (1LL << i);
        }
    }
    return res;
}

void search(long long vertex) {
    used.insert(vertex);
    visited++;
    if (visited > limit) {
        decisionOverflow = true;
        return;
    }
    for (int i = 0; i < k; ++i) {
        long long v = (vertex ^ (1LL << i));
        if (v == destination) {
            decisionFound = true;
            return;
        }
        if (used.find(v) == used.end() && s.find(v) == s.end()) {
            search(v);
            if (decisionOverflow || decisionFound) {
                return;
            }
        }
    }
}

void setup(long long dest) {
    used.clear();
    visited = 0;
    destination = dest;
    decisionOverflow = false;
    decisionFound = false;
}

bool research() {
    limit = n * k + 1;
    setup(nodeB);
    search(nodeA);
    if (decisionFound) {
        return true;
    } else {
        if (decisionOverflow) {
            setup(nodeA);
            search(nodeB);
            return (decisionOverflow || decisionFound);
        }
    }
    return false;
}

int main() {
    char be[MAXN], en[MAXN], node[MAXN];
    scanf("%d%d", &k, &n);
    scanf("%s %s", be, en);
    nodeA = translate(be);
    nodeB = translate(en);
    for (int i = 0; i < n; ++i) {
        scanf("%s", node);
        s.insert(translate(node));
    }
    printf(research() ? "TAK\n" : "NIE\n");
    return 0;
}

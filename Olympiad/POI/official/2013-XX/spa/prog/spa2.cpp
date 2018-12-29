/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Miroslaw Michalski                            *
 *   Zlozonosc czasowa:    O(n^2 * k)                                    *
 *   Zlozonosc pamieciowa: O(nk)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <ext/hash_set>

using __gnu_cxx::hash_set;
using std::set;
using std::vector;

const int MAXN = 123;
const int MAXM = 5000033;
long long queue[MAXM];
int k, n, visited, limit;
long long nodeA, nodeB, destination;
bool decisionOverflow, decisionFound;


struct hasher {
    long long operator()(const long long a) const {
        return a;
    }
};

struct eq {
    int operator()(const long long a, const long long b) const {
        return a == b;
    }
};

hash_set<long long, hasher, eq> s, used;


long long translate(char* c) {
    long long res = 0;
    for (int i = 0; i < k; ++i) {
        if (c[i] == '1') {
            res += (1LL << i);
        }
    }
    return res;
}

void search(long long node) {
    int head = 0, tail = 0;
    long long vertex, v;
    queue[tail++] = node;
    used.insert(node);
    visited++;
    while (head < tail) {
        vertex = queue[head++];
        for (int i = 0; i < k; ++i) {
            v = (vertex ^ (1LL << i));
            if (v == destination) {
                decisionFound = true;
                return;
            }
            if (used.find(v) == used.end() && s.find(v) == s.end()) {
                used.insert(v);
                visited++;
                if (visited > limit) {
                    decisionOverflow = true;
                    return;
                }
                queue[tail++] = v;
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

/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O((q+n) log* (q+n))                           *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Nie rozwaza przypadku gdy:                    *
 *                         liczba procesorow > liczba wierzcholkow       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define F first
#define S second

const int MAXN = 1000001;
const int MAXQ = 1000001;

int n, m, t[MAXN], q[MAXQ], d[MAXN], result[MAXN], p[3*MAXN+1], maxD = 0;
vector<int> adj[MAXN], pos[MAXN];
pair<int,int> block[3*MAXN+1];

int FindSet(int u) {
    if (u != p[u])
        p[u] = FindSet(p[u]);
    return p[u];
}

void Union(int a, int b) {
    p[FindSet(a)] = FindSet(b);
}

void Dfs(int u) {
    for (unsigned i = 0; i < adj[u].size(); i++) {
        d[adj[u][i]] = d[u]+1;
        Dfs(adj[u][i]);
    }
    block[d[u]].F++;
    maxD = max(maxD, d[u]);
}

int main() {
    int ret, curResult;

    ret = scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++)
        ret = scanf("%d", &q[i]);

    for (int i = 1; i < n; i++) {
        ret = scanf("%d", &t[i]);
        t[i]--;

        adj[t[i]].push_back(i);
    }

    if (ret < 0)
        return 1;

    Dfs(0);

    for (int i = 0; i <= maxD; i++) {
        block[i].S = 1;
        pos[block[i].F].push_back(i);
    }

    curResult = maxD;
    result[n] = curResult+1;

    for (int i = 0; i <= 3*n; i++)
        p[i] = i;

    for (int i = n; i > 1; i--) {
        for (unsigned j = 0; j < pos[i].size(); j++) {
            int x = pos[i][j];

            if (x != FindSet(x))
                continue;

            if (block[FindSet(x+1)].F == block[x].F) {
                block[FindSet(x+1)].S += block[x].S;
                Union(x, FindSet(x+1));
            }
        }

        for (unsigned j = 0; j < pos[i].size(); j++) {
            int x = pos[i][j], more = 0;

            if (x != FindSet(x))
                continue;

            if (block[FindSet(x+1)].F == block[x].F) {
                block[FindSet(x+1)].S += block[x].S;
                Union(x, FindSet(x+1));

                continue;
            }

            if (block[x].F <= i-1)
                continue;

            do {
                int nextBlock;

                more += (block[x].F-(i-1))*block[x].S;
                if (more > 0) {
                    nextBlock = block[FindSet(x+1)].F*block[FindSet(x+1)].S+more;

                    if (nextBlock > i-1) {
                        more = nextBlock-max(1,block[FindSet(x+1)].S)*(i-1);
                        block[x].F = i-1;
                        block[FindSet(x+1)].F = i-1;
                        curResult -= block[FindSet(x+1)].S;
                        block[FindSet(x+1)].S = max(1,block[FindSet(x+1)].S);
                        curResult += block[FindSet(x+1)].S;
                        pos[block[x].F].push_back(x);
                        pos[block[FindSet(x+1)].F].push_back(FindSet(x+1));
                    }
                    else if (more > 0) {
                        more = 0;
                        block[x].F = i-1;
                        block[FindSet(x+1)].F = nextBlock;
                        pos[block[x].F].push_back(x);
                        pos[block[FindSet(x+1)].F].push_back(FindSet(x+1));
                        if (block[FindSet(x+1)].S == 0) {
                            block[FindSet(x+1)].S = 1;
                            curResult++;
                        }
                    }
                    x = FindSet(x+1);
                }
            } while (more > 0);
        }

        pos[i].clear();

        result[i-1] = curResult+1;
    }

    for (int i = 0; i < m; i++) {
        if (i > 0) printf(" ");
        printf("%d", result[q[i]]);
    }
    printf("\n");

    return 0;
}

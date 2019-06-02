/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n*sqrt(n))                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long int LL;

const int MAXN = 250001;

int N, K, sizeTree[MAXN], T[MAXN];
LL sumTree[MAXN];
vector<int> adj[MAXN];
bool visited[MAXN], dp[MAXN];

void Dfs(int u) {
    visited[u] = true;
    sizeTree[u] = 1;

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]]) {
            Dfs(adj[u][i]);
            sizeTree[u] += sizeTree[adj[u][i]];
            sumTree[u] += sumTree[adj[u][i]];
        }
}

void Compute(int u) {
    visited[u] = true;
    sizeTree[u] = 1;

    for (int i = 0; i < (int)adj[u].size(); i++)
        if (!visited[adj[u][i]]) {
            Compute(adj[u][i]);
            sizeTree[u] += sizeTree[adj[u][i]];
            sumTree[u] += sumTree[adj[u][i]]+sizeTree[adj[u][i]];
        }
}

int main() {
    int centroid = -1;
    LL result = 0;

    scanf("%d", &N);

    for (int i = 0; i < N-1; i++) {
        int u, v;

        scanf("%d%d", &u, &v);
        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    Dfs(0);

    for (int i = 0; i < N; i++) {
        int maxSizeTree = 0, outSizeTree = N-1;

        for (int j = 0; j < (int)adj[i].size(); j++) {
            if (sizeTree[adj[i][j]] > sizeTree[i])
                continue;
            maxSizeTree = max(maxSizeTree, sizeTree[adj[i][j]]);
            outSizeTree -= sizeTree[adj[i][j]];
        }

        //printf("i = %d, maxSizeTree = %d, outSizeTree = %d\n", i+1, maxSizeTree, outSizeTree);

        if ((outSizeTree <= N/2) && (maxSizeTree <= N/2)) {
            centroid = i;
            break;
        }
    }

    //printf("centroid = %d\n", centroid+1);

    fill(visited, visited+N, false);
    fill(sizeTree, sizeTree+N, 0);

    Compute(centroid);

    K = N;
    N = (int)adj[centroid].size();

    for (int i = 0; i < N; i++) {
        T[sizeTree[adj[centroid][i]]]++;
        result += sumTree[adj[centroid][i]]+sizeTree[adj[centroid][i]];
    }

    dp[0] = true;
    for (int i = 1; i <= K; i++) {
        if (T[i] > 0) {
            int amount = T[i], lastAmount = 0;

            for (int j = 1; j <= amount; j*=2) {
                int curDenomination;

                if (j <= amount/2)
                    curDenomination = i*j;
                else
                    curDenomination = i*(amount-lastAmount);

                //printf("denomination = %d\n", curDenomination);

                for (int k = K; k >= curDenomination; k--)
                    if (dp[k-curDenomination])
                        dp[k] = true;

                lastAmount = j;
            }
        }
    }

    int best = 0;

    for (int i = 1; i <= K; i++)
        if ((max(i, K-1-i) < max(best, K-1-best)) && (dp[i]))
            best = i;

    //printf("best = %d\n", best);

    result += (LL)(K-1-best)*best;

    printf("%d %Ld\n", K-1, result);

    return 0;
}

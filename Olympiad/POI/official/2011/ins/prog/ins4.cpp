/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe - sprytniejsze              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
#include <cassert>

typedef long long LL; // tylko po to aby sprawdzic jak zachowa sie dla intow

const int MAXN = 1000123;
const int NOANS = -1;


int deg[MAXN];
std::vector<int> v[MAXN];
int n;

bool used[MAXN];
int myDeg[MAXN], father[MAXN], sizeOfSubtree[MAXN], depth[MAXN], maxSubtree[MAXN];
LL cost[MAXN];

void dfs(int x) {
    used[x] = true;
    for(size_t i = 0; i < v[x].size(); i++) if (!used[v[x][i]]) {
        father[v[x][i]] = x;
        dfs(v[x][i]);
    }
}

std::vector<int> getCands(int root) {
    std::vector<int> cands;
    for(int i = 0; i < n; i++) {
        myDeg[i] = deg[i];
        used[i] = false;
        father[i] = -1;
        
        sizeOfSubtree[i] = 1;
        maxSubtree[i] = 0;
    }
    dfs(root);

    std::queue<int> q;
    for(int i = 0; i < n; i++) if (myDeg[i] == 1) {
        q.push(i);
    }
    while (!q.empty()) {
        int wz1 = q.front(); q.pop();
        myDeg[father[wz1]]--;
        if (std::max(n - sizeOfSubtree[wz1], maxSubtree[wz1]) <= n/2) {
            cands.push_back(wz1);
        }
        
        sizeOfSubtree[father[wz1]] += sizeOfSubtree[wz1];
        maxSubtree[father[wz1]] = std::max(maxSubtree[father[wz1]], sizeOfSubtree[wz1]);

        if (myDeg[father[wz1]] == 1 && father[wz1] != -1) {
            q.push(father[wz1]);
        }
    }
    return cands;
}

LL anal(int root) {
// liczymy odpowiedz dla root'a max. poddrzewo == n/2
    for(int i = 0; i < n; i++) {
        myDeg[i] = deg[i];
        used[i] = false;
        father[i] = -1;
        
        sizeOfSubtree[i] = 1;
        cost[i] = 0;
        depth[i] = 0;
    }
    dfs(root);

    std::queue<int> q;
    for(int i = 0; i < n; i++) if (myDeg[i] == 1) {
        q.push(i);
    }

    while (!q.empty()) {
        int wz1 = q.front(); q.pop();
        myDeg[father[wz1]]--;
        
        sizeOfSubtree[father[wz1]] += sizeOfSubtree[wz1];
        cost[father[wz1]] += (2L * sizeOfSubtree[wz1] + cost[wz1]);
        depth[father[wz1]] = std::max(depth[father[wz1]], depth[wz1] + 1);

        if (myDeg[father[wz1]] == 1 && father[wz1] != -1) {
            q.push(father[wz1]);
        }
    }

    int maxDepth = 0;
    for(size_t i = 0; i < v[root].size(); i++) {
        maxDepth = std::max(maxDepth, depth[v[root][i]]);
    }
    for(size_t i = 0; i < v[root].size(); i++) {
        if (sizeOfSubtree[v[root][i]] ==  n/2) {
            maxDepth = depth[v[root][i]];
        }
    }
    return cost[root] - (maxDepth + 1);
}

int main() {
    int a, b;
    scanf("%d", &n);
    if (n == 1) {
        printf("0\n");
        return 0;
    }
    for(int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        v[a].push_back(b);
        v[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }

    std::vector<int> getCandidates = getCands(n - 1);
    if (getCandidates.size() == 1) {
        int a = getCandidates[0]; 
        for(int i = 0; i < a; i++) {
            printf("%d\n", NOANS);
        }
        printf("%lld\n", anal(a));
        for(int i = a + 1; i < n; i++) {
            printf("%d\n", NOANS);
        }
    } else if (getCandidates.size() == 2) {
        int a = getCandidates[0], b = getCandidates[1];
        if (a > b) std::swap(a, b);
        for(int i = 0; i < a; i++) {
            printf("%d\n", NOANS);
        }
        printf("%lld\n", anal(a));
        for(int i = a + 1; i < b; i++) {
            printf("%d\n", NOANS);
        }
        printf("%lld\n", anal(b));
        for(int i = b + 1; i < n; i++) {
            printf("%d\n", NOANS);
        }
    } else {
        assert(false);
    }
    return 0;
}


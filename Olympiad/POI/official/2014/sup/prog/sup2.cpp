/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(q+n)                                        *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

const int N = 1000000;

int n, queries, query[N], depth[N];

int tasks[N], block_size[N];
bool first_in_block[N];
vector<int> by_tasks[N+1];
int length, result[N+1];

int main() {
    int ret;
    ret = scanf("%d%d", &n, &queries);
    for (int i = 0; i < queries; ++i) {
        ret = scanf("%d", &query[i]);
        query[i] = min(query[i], n);
    }
    depth[0] = 0;
    for (int i = 1; i < n; ++i) {
        int parent;
        ret = scanf("%d", &parent);
        depth[i] = 1 + depth[parent - 1];
    }

    for (int i = 0; i < n; ++i) {
        tasks[i] = 0;
        block_size[i] = 1;
        first_in_block[i] = true;
    }
    length = 0;
    for (int i = 0; i < n; ++i) {
        tasks[depth[i]]++;
        length = max(length, 1 + depth[i]);
    }
    for (int i = 0; i < n; i++) if (tasks[i] > 0) by_tasks[tasks[i]].push_back(i);
    result[n] = length;

    for (int k = n - 1; k > 0; --k) {
        for (int it = 0; it < (int)by_tasks[k+1].size(); ++it) {
            int x = by_tasks[k+1][it];
            if (!first_in_block[x] || tasks[x] != (k+1)) continue;
            int delta = block_size[x];
            tasks[x]--;
            by_tasks[tasks[x]].push_back(x);
            while(delta > 0) {
                int y = x + block_size[x];
                if (block_size[y] == 1 && (tasks[y] + delta) < k) {
                    tasks[y] += delta;
                    delta = 0;
                    by_tasks[tasks[y]].push_back(y);
                } else {
                    delta -= (k - tasks[y]) * block_size[y];
                    block_size[x] += block_size[y];
                    first_in_block[y] = 0;
                }
                length = max(length, 1 + y);
            }
        }
        result[k] = length;
    }

    for (int i = 0; i < queries; ++i)
        printf(i > 0 ? " %d" : "%d", result[query[i]]);
    printf("\n");
    if(ret<0) return 0;
    return 0;
}


#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAXR = 600, MAXS = 1100, MAXN = 300000, RP[] = {0, 1, 0, -1}, SP[] = {1, 0, -1, 0};

int n, d[MAXN], r[MAXN], b[MAXR][MAXS], x[MAXR][MAXS];
vector <int> p, v[MAXN];
queue <int> q;

int main() {
    scanf("%d", &n);

    int br = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < 2 * (n - (i & 1)); ++j) {
            scanf("%d", b[i] + j + (i & 1));
            x[i][j + (i & 1)] = br;

            br += j & 1;
        }

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < 2 * n; ++j)
            for(int k = 0; k < 4; ++k) {
                int rp = i + RP[k], sp = j + SP[k];
                if(rp >= 0 && rp < n && sp >= 0 && sp < 2 * n && x[rp][sp] != x[i][j] && b[rp][sp] == b[i][j])
                    v[x[i][j]].push_back(x[rp][sp]);
            }

    memset(d, 0xff, sizeof(d));

    d[0] = 0;
    r[0] = -1;

    for(q.push(0); q.size(); q.pop()) {
        int c = q.front();
        for(int i = 0; i < v[c].size(); ++i) {
            int o = v[c][i];
            if(d[o] == -1) {
                d[o] = d[c] + 1;
                r[o] = c;
                q.push(o);
            }
        }
    }

    int f;
    for(f = n * n - n / 2 - 1; d[f] == -1; --f);

    for(int x = f; x != -1; x = r[x])
        p.push_back(x);

    printf("%d\n", p.size());

    for(int i = p.size() - 1; i >= 0; --i)
        printf("%d ", p[i] + 1);

    printf("\n");

    return 0;
}

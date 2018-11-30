/* Solution for task "Escape"
 * Linas Petrauskas
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 250
#define MAXV (MAXN * 2 + 3)
#define MAXVISION 100
#define INFINITY 1000000
#define UNDEFINED -1

    typedef struct flow_network {
        int n, source, sink;
        int cap[MAXV][MAXV];
    } flow_network;

void form_flow_network(flow_network *g, int n, int w, int *x, int *y);
void find_max_flow(flow_network *g, int f[MAXV][MAXV]);

int main(void)
{
    int l, w, n, i;
    int x[MAXN], y[MAXN];
    flow_network g;
    int flow[MAXV][MAXV], flow_value;

    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);

    scanf("%d%d%d", &l, &w, &n);    
    for (i = 0; i < n; i++)
        scanf("%d%d", &x[i], &y[i]);
    
    form_flow_network(&g, n, w, x, y);
    find_max_flow(&g, flow);
    
    flow_value = 0;
    for (i = 0; i < g.n; i++)
        flow_value += flow[g.source][i];

    printf("%d\n", flow_value);
    
    return 0;
}

int are_close_enough(int x1, int y1, int x2, int y2)
{
    if ((abs(x1 - x2) > 2 * MAXVISION) || (abs(y1 - y2) > 2 * MAXVISION))
        return 0;
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= 4 * MAXVISION * MAXVISION);
}

void form_flow_network(flow_network *g, int n, int w, int *x, int *y)
{
    int i, j;
    int s, t;

    g->n = 2 * n + 2;
    g->source = s = 2 * n;
    g->sink = t = 2 * n + 1;

    // default capacities
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->cap[i][j] = 0;

    for (i = 0; i < n; i++) {
        g->cap[i][n + i] = 1;                   // i-in to i-out
        if (w - y[i] <= MAXVISION)
            g->cap[n + i][t] = INFINITY;        // i-out to sink
        if (y[i] - 0 <= MAXVISION)
            g->cap[s][i] = INFINITY;            // source to i-in
        for (j = i + 1; j < n; j++)
            if (are_close_enough(x[i], y[i], x[j], y[j])) {
                g->cap[n + i][j] = INFINITY;    // i-out to j-in
                g->cap[n + j][i] = INFINITY;    // j-out to i-in
            }
    }
}

void bfs(flow_network *g, int *parent)
{
    int queue[MAXV], b, e;
    int visited[MAXV];
    int v, u;

    for (v = 0; v < g->n; v++) {
        visited[v] = 0;
        parent[v]  = UNDEFINED;
    }
    
    b = e = 0;
    queue[e++] = g->source;
    visited[g->source] = 1;

    while (b < e) {
        v = queue[b++];
        for (u = 0; u < g->n; u++)
            if (g->cap[v][u] > 0 && !visited[u]) {
                visited[u] = 1;
                parent[u]  = v;
                queue[e++] = u;
            }
    }
}

void augment_flow_along_path(flow_network *g, int f[MAXV][MAXV], int *parent)
{
    int u, v;

    for (v = g->sink, u = parent[v]; u != UNDEFINED; v = u, u = parent[u]) {
        f[u][v]++;
        f[v][u]--;
        g->cap[u][v]--;
        g->cap[v][u]++;
        // the flow and capacities are increased/decreased by one, which would
        // be innefficient in general case, but in this task every path augments
        // flow by one.
    }
}

void find_max_flow(flow_network *g, int f[MAXV][MAXV])
{
    int parent[MAXV], i, j;

    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++)
            f[i][j] = 0;

    // Ford-Fulkerson method: find an augmenting path and augment flow along that path.
    // (the flow is maximum if and only if no augmenting path exists.)    
    bfs(g, parent);
    while (parent[g->sink] != UNDEFINED) {  // augmenting path found
        augment_flow_along_path(g, f, parent);
        bfs(g, parent);
    }
}


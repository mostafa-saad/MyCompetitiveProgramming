#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
 
const int mod = 1e9;
 
vector<int> vx[100005],vy[100005];
vector<int> nx[100005],ny[100005];
vector<int> gx[100005],gy[100005];
 
int sx[100005], sy[100005];
 
int piv;
 
void const_graph(int n, vector<int> *v, vector<int> *c, vector<int> *g, int* s){
    piv = 0;
    for (int i=0; i<n; i++) {
        sort(v[i].begin(),v[i].end());
        c[i].resize(v[i].size());
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<v[i].size(); j++) {
            if(j && v[i][j-1] + 1 == v[i][j]){
                c[i][j] = c[i][j-1];
            }
            else c[i][j] = ++piv;
            s[c[i][j]]++;
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<v[i].size(); j++) {
            auto it = lower_bound(v[i+1].begin(),v[i+1].end(),v[i][j]);
            if(it != v[i+1].end() && *it == v[i][j]){
                int col = c[i+1][it - v[i+1].begin()];
                if(!g[c[i][j]].empty() && g[c[i][j]].back() == col){
                    continue;
                }
                else{
                    g[c[i][j]].push_back(col);
                    g[col].push_back(c[i][j]);
                }
            }
        }
    }
}
 
int *size;
vector<int> *graph;
int size2[100005];
 
int dfs(int x, int pa){
    int r = size[x];
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i] == pa) continue;
        r += dfs(graph[x][i],x);
    }
    size2[x] = r;
    return r;
}
 
long long solve(int n){
    memset(size2,0,sizeof(size2));
    dfs(1,0);
    long long ret = 0;
    for (int i=1; size[i]; i++) {
        for (int j=0; j<graph[i].size(); j++) {
            if(i > graph[i][j]) continue;
            int p = min(size2[i],size2[graph[i][j]]);
            ret += 1ll * (n-p) * p;
        }
    }
    return ret;
}
 
int DistanceSum(int N, int* X, int* Y){
    int minX = *min_element(X,X+N);
    int minY = *min_element(Y,Y+N);
    for (int i=0; i<N; i++) {
        X[i] -= minX;
        Y[i] -= minY;
    }
    for (int i=0; i<N; i++) {
        vx[X[i]].push_back(Y[i]);
    }
    const_graph(N,vx,nx,gx,sx);
    for (int i=0; i<N; i++) {
        vy[Y[i]].push_back(X[i]);
    }
    const_graph(N,vy,ny,gy,sy);
    long long ret = 0;
    size = sx, graph = gx;
    ret += solve(N);
    size = sy, graph = gy;
    ret += solve(N);
    return ret % mod;
}
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
int x[100005], y[100005], n, w;
pi graph[100005][4];
 
int ang(int i, int j){
    if(x[i] == x[j]){
        if(y[i] < y[j]) return 1;
        return 3;
    }
    else{
        if(x[i] < x[j]) return 0;
        return 2;
    }
}
 
int vis[100005][4], piv;
int idx[100005];
 
vector<int> comp[200005];
 
void dfs(int x, int d){
    if(vis[x][d]) return;
    vis[x][d] = piv;
    comp[piv].push_back(x);
    for (int i=5; i>=2; i--) {
        if(graph[graph[x][d].first][(d+i)%4].second){
            dfs(graph[x][d].first,(d+i)%4);
            return;
        }
    }
}
 
int pa[200005], pb[200005];
vector<int> graph2[200005];
 
int vis2[200005], dist[200005];
int vis3[200005];
 
vector<int> inner;
 
void dfs2(int pos){
    if(vis3[pos]) return;
    for (int i=0; i<comp[pos].size(); i++) {
        inner.push_back(comp[pos][i]);
    }
    vis3[pos] = 1;
    for (int i=0; i<graph2[pos].size(); i++){
        dfs2(graph2[pos][i]);
    }
}
 
vector<int> ret;
 
void bfs(int x){
    vis2[x] = 1;
    queue<int> q,d;
    q.push(x);
    d.push(0);
    while (!q.empty()) {
        int qf = q.front();
        int df = d.front();
        q.pop();
        d.pop();
        dist[qf] = df;
        for (int i=0; i<graph2[qf].size(); i++) {
            if(!vis2[graph2[qf][i]]){
                q.push(graph2[qf][i]);
                d.push(df+1);
                vis2[graph2[qf][i]] = 1;
            }
        }
    }
}
 
int main(){
    pi t(1e9,1e9);
    int p = 0;
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&x[i],&y[i]);
        if(t > pi(x[i],y[i])){
            t = pi(x[i],y[i]);
            p = i;
        }
    }
    scanf("%d",&w);
    for (int i=1; i<=w; i++) {
        int a,b;
        scanf("%d %d",&pa[i],&pb[i]);
        a = pa[i], b = pb[i];
        graph[a][ang(a,b)] = pi(b,i);
        graph[b][ang(b,a)] = pi(a,i);
    }
    for (int i=1; i<=n; i++){
        for (int j=0; j<4; j++) {
            if(graph[i][j].second && !vis[i][j]){
                piv++;
                dfs(i,j);
            }
        }
    }
    for (int i=1; i<=w; i++){
        int a = pa[i], b = pb[i];
        int v1 = vis[a][ang(a,b)];
        int v2 = vis[b][ang(b,a)];
        graph2[v1].push_back(v2);
        graph2[v2].push_back(v1);
    }
    for (int i=1; i<=piv; i++) {
        if(!vis3[i]){
            inner.clear();
            dfs2(i);
            pi ext(1e9,1e9);
            int p = 0;
            for (int i=0; i<inner.size(); i++) {
                if(ext > pi(x[inner[i]],y[inner[i]])){
                    ext = pi(x[inner[i]],y[inner[i]]);
                    p = inner[i];
                }
            }
            if(vis[p][1]){
                bfs(vis[p][1]);
            }
            else{
                bfs(vis[p][0]);
            }
        }
    }
    for (int i=1; i<=w; i++){
        int a = pa[i], b = pb[i];
        int v1 = vis[a][ang(a,b)];
        int v2 = vis[b][ang(b,a)];
        if(dist[v1] == dist[v2]){
            ret.push_back(i);
        }
    }
    printf("%d\n",(int)ret.size());
    for (int i=0; i<ret.size(); i++){
        printf("%d\n",ret[i]);
    }
}

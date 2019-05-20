#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
int s,e;
int n,m,k,sp[2005];
int topo[2005];
vector<pi> graph[2005];
 
vector<int> sp_tree[2005];
int dist[2005], ed_dist[2005];
int vis[2005], lab[2005], par[2005];
 
priority_queue<pi,vector<pi>,greater<pi> > pq;
 
void dfs(int x, int l){
    l = max(l,topo[x]);
    lab[x] = l;
    for (int i=0; i<sp_tree[x].size(); i++) {
        dfs(sp_tree[x][i],l);
    }
}
 
void input(){
    memset(topo,-1,sizeof(topo));
    memset(dist,0x3f,sizeof(dist));
    scanf("%d %d %d %d",&n,&m,&s,&e);
    for (int i=0; i<m; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    scanf("%d",&k);
    for (int i=1; i<=k; i++) {
        scanf("%d",&sp[i]);
        topo[sp[i]] = i;
    }
    pq.push(pi(0,s));
    dist[s] = 0;
    while (!pq.empty()){
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        if(t.second != s){
            sp_tree[par[t.second]].push_back(t.second);
        }
        for (int i=0; i<graph[t.second].size(); i++) {
            pi edg = graph[t.second][i];
            if(topo[edg.second] == topo[t.second] + 1 || dist[edg.second] > edg.first + t.first){
                dist[edg.second] = edg.first + t.first;
                par[edg.second] = t.second;
                pq.push(pi(edg.first + t.first,edg.second));
            }
        }
    }
    memset(vis,0,sizeof(vis));
    pq.push(pi(0,e));
    while (!pq.empty()) {
        pi t = pq.top();
        pq.pop();
        if(vis[t.second]) continue;
        vis[t.second] = 1;
        ed_dist[t.second] = t.first;
        for (int i=0; i<graph[t.second].size(); i++) {
            pi edg = graph[t.second][i];
            pq.push(pi(edg.first + t.first,edg.second));
        }
    }
    dfs(s,1);
}
 
vector<int> add[2005], del[2005];
multiset<int> ms;
 
int main(){
    input();
    for (int i=1; i<=n; i++) {
        for (int j=0; j<graph[i].size(); j++) {
            if(abs(topo[i] - topo[graph[i][j].second]) == 1){
                continue;
            }
            int st = i;
            int ed = graph[i][j].second;
            if(lab[st] >= lab[ed]) continue;
            int ret = graph[i][j].first + dist[st] + ed_dist[ed];
            add[lab[st]].push_back(ret);
            del[lab[ed]].push_back(ret);
        }
    }
    for (int i=1; i<k; i++) {
        for (int j=0; j<del[i].size(); j++) {
            ms.erase(ms.find(del[i][j]));
        }
        for (int j=0; j<add[i].size(); j++) {
            ms.insert(add[i][j]);
        }
        if(ms.empty()) puts("-1");
        else printf("%d\n",*ms.begin());
    }
}
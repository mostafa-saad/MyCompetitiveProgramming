#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
   
struct disj{
    int pa[50005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        pa[q] = p;
    }
}disj;
   
int n, m;
int st[200005], ed[200005], x[200005];
   
vector<int> graph[20005], rev[20005];
vector<int> dfn;
 
int comp[20005], vis[20005], indeg[20005], piv;
int lab[20005], arb[20005];
   
void dfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for(auto &i : graph[x]){
        dfs(i);
    }
    dfn.push_back(x);
}
   
void rdfs(int x){
    if(vis[x]) return;
    vis[x] = 1;
    comp[x] = piv;
    for(auto &i : rev[x]){
        rdfs(i);
    }
}
   
void scc(){
    for(int i=1; i<=n; i++){
        if(!vis[i]) dfs(i);
    }
    memset(vis,0,sizeof(vis));
    reverse(dfn.begin(), dfn.end());
    for(auto &i : dfn){
        if(!vis[i]){
            piv++;
            arb[piv] = i;
            rdfs(i);
        }
    }
    memset(vis,0,sizeof(vis));
    for(int i=1; i<=n; i++){
        for(auto &j : graph[i]){
            if(comp[i] != comp[j]){
                indeg[comp[j]]++;
            }
        }
    }
}
   
int comp_zeros[20005];
bool is_root[20005];
   
vector<int> dag[20005];
vector<int> vist;
int dfn2[20005], piv2;
   
void dfs2(int x){
    if(vis[x]) return;
    vis[x] = 1;
    for(auto &i : dag[x]){
        dfs2(i);
    }
    vist.push_back(x);
    dfn2[x] = ++piv2;
}
   
bool topo(){
    for(int i=1; i<=n; i++){
        if(is_root[i] && !vis[i]){
            dfs2(i);
        }
    }
    for(int i=1; i<=n; i++){
        for(auto &j : dag[i]){
            if(dfn2[i] <= dfn2[j]) return 1;
        }
    }
    return 0;
}
   
void dfs3(int x, int l){
    if(lab[x]) return;
    lab[x] = l;
    for(auto &i : graph[x]){
        dfs3(i,l);
    }
}
   
int main(){
    scanf("%d %d",&n,&m);
    disj.init(n);
    for(int i=0; i<m; i++){
        scanf("%d %d %d",&st[i],&ed[i],&x[i]);
        if(x[i] == 0){
            graph[st[i]].push_back(ed[i]);
            rev[ed[i]].push_back(st[i]);
            disj.uni(st[i], ed[i]);
        }
    }
    scc();
    for(int i=1; i<=piv; i++){
        if(indeg[i] == 0){
            int par = disj.find(arb[i]);
            if(comp_zeros[par]){
                puts("-1");
                return 0;
            }
            comp_zeros[par]++;
            is_root[arb[i]] = 1;
            dfs3(arb[i], arb[i]);
        }
    }
    for(int i=0; i<m; i++){
        if(x[i]){
            dag[lab[st[i]]].push_back(lab[ed[i]]);
        }
    }
    if(topo()){
        puts("-1");
        return 0;
    }
    for(auto &i : vist){
        printf("%d ",i);
    }
    for(int i=1; i<=n; i++){
        if(!is_root[i]) printf("%d ",i);
    }
}
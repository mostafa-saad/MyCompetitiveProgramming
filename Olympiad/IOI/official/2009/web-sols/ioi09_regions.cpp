#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
 
int n,r,q;
int grp[200005];
 
vector<int> graph[200005];
vector<int> reg[25005];
vector<int> rege[25005];
 
int dfn[200005], sz[200005], piv;
 
int dfs(int x){
    dfn[x] = ++piv;
    sz[dfn[x]] = 1;
    reg[grp[x]].push_back(dfn[x]);
    for (int i=0; i<graph[x].size(); i++) {
        sz[dfn[x]] += dfs(graph[x][i]);
    }
    rege[grp[x]].push_back(dfn[x] + sz[dfn[x]] - 1);
    return sz[dfn[x]];
}
 
map<int,int> mp;
 
int query(int x, int y){
    int ret = 0;
    for (int i=0; i<reg[x].size(); i++) {
        int piv = reg[x][i];
        int cnt = (int)(lower_bound(reg[y].begin(),reg[y].end(),piv + sz[piv]) - lower_bound(reg[y].begin(),reg[y].end(),piv));
        ret += cnt;
    }
    return ret;
}
 
int query2(int x, int y){
    int ret = 0;
    for (int i=0; i<reg[y].size(); i++) {
        int piv = reg[y][i];
        int cnt1 = (int)(upper_bound(reg[x].begin(),reg[x].end(),piv) - reg[x].begin());
        int cnt2 = (int)(lower_bound(rege[x].begin(),rege[x].end(),piv) - rege[x].begin());
        ret += cnt1 - cnt2;
    }
    return ret;
}
 
int main(){
    scanf("%d %d %d",&n,&r,&q);
    scanf("%d",&grp[1]);
    for (int i=2; i<=n; i++) {
        int p;
        scanf("%d %d",&p,&grp[i]);
        graph[p].push_back(i);
    }
    dfs(1);
    for (int i=1; i<=r; i++) {
        sort(rege[i].begin(),rege[i].end());
    }
    while (q--) {
        int x,y;
        scanf("%d %d",&x,&y);
        if(mp.find(x*r + y) != mp.end()){
            printf("%d\n",mp[x*r+y]);
        }
        else{
            int t;
            if(reg[x].size() < reg[y].size()) t = query(x,y);
            else t = query2(x,y);
            mp[x*r+y] = t;
            printf("%d\n",t);
        }
    }
}
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> pi;
 
vector<pi> graph[101];
 
int n,k,w[101],p[101];
int dist[101];
int dp[101][101][51];
 
void dfs(int x, int d){
    dist[x] = d;
    for (int i=0; i<graph[x].size(); i++) {
        dfs(graph[x][i].second,d+graph[x][i].first);
    }
}
 
int f(int x, int csub, int nearest, int left){
    if(graph[x].size() == csub){
        if(csub == 0){
            if(left == 1) return 0;
            else if(left == 0) return w[x] * (dist[x] - dist[nearest]);
            return 1e9;
        }
        else return left ? 1e9 : 0;
    }
    if(~dp[graph[x][csub].second][nearest][left]) return dp[graph[x][csub].second][nearest][left];
    int ret = 1e9;
    if(csub == 0){
        for (int i=0; i<left; i++) {
            ret = min(ret,f(graph[x][csub].second,0,x,i) + f(x,csub+1,x,left-i-1));
        }
        for (int i=0; i<=left; i++) {
            ret = min(ret,f(graph[x][csub].second,0,nearest,i) + f(x,csub+1,nearest,left-i) + w[x] * (dist[x] - dist[nearest]));
        }
    }
    else{
        for (int i=0; i<=left; i++) {
            ret = min(ret,f(graph[x][csub].second,0,nearest,i) + f(x,csub+1,nearest,left-i));
        }
    }
    return dp[graph[x][csub].second][nearest][left] = ret;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&n,&k);
    for (int i=1; i<=n; i++) {
        int q;
        scanf("%d %d %d",&w[i],&p[i],&q);
        graph[p[i]].push_back(pi(q,i));
    }
    dfs(0,0);
    printf("%d",f(0,0,0,k));
}

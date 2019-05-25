#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;
typedef pair<lint,lint> pii;
 
vector<pi> graph[100005];
 
int n, s[100005], v[100005];
lint dp[100005];
 
pii stk[100005];
 
inline lint func(pii x, int t){
    return x.first * t + x.second;
}
 
inline bool cross(pii a, pii b, pii c){
    return (1.0 * (b.second - a.second) / (a.first - b.first) >= 1.0 * (c.second - b.second) / (b.first - c.first));
}
 
void process(int x, int& piv, int dist){
    int st, ed, m;
    if(x != 1){
        st = 0, ed = piv - 1;
        while (st != ed){
            m = (st + ed)/2;
            if(func(stk[m],v[x]) <= func(stk[m+1],v[x])){
                ed = m;
            }
            else st = m+1;
        }
        dp[x] = func(stk[st],v[x]) + 1ll * dist * v[x] + s[x];
    }
    pii tmp = pii(-dist,dp[x]);
    st = 0, ed = piv-1;
    while (st < ed){
        m = (st + ed) / 2;
        if(cross(stk[m],stk[m+1],tmp)){
            ed = m;
        }
        else st = m+1;
    }
    piv = ed + 1;
}
 
void solve(int x, int piv, int pa, int dist){
    process(x,piv,dist);
    pii bk = stk[piv];
    stk[piv] = pii(-dist,dp[x]);
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i].second != pa){
            solve(graph[x][i].second,piv+1,x,dist + graph[x][i].first);
        }
    }
    stk[piv] = bk;
}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int s,e,x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x,e));
        graph[e].push_back(pi(x,s));
    }
    for (int i=2; i<=n; i++) {
        scanf("%d %d",&s[i],&v[i]);
    }
    solve(1,0,0,0);
    for (int i=2; i<=n; i++) {
        printf("%lld ",dp[i]);
    }
}
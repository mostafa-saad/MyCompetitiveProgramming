#include <cstdio>
#include <cstring>
#include <cstdlib>
struct vec{int p,x,t;};
 
int n,adj[1005][1005];
char dp[1005][1005][2];
vec obj[1005][1005][2];
 
int norm(int x){
    if(x <= 0) return x+n;
    if(x > n) return x-n;
    return x;
}
 
int f(int p, int x, int turn_left){
    if(~dp[p][x][turn_left]) return dp[p][x][turn_left];
    if(turn_left){
        if(norm(p-x) == n-1) return 1;
        int p1 = norm(p+1), p2 = norm(x-1);
        if(adj[x][p1] && f(x,p1,0)){
            vec &t = obj[p][x][turn_left];
            t.p = x;
            t.x = p1;
            t.t = 0;
            return dp[p][x][turn_left] = 1;
        }
        if(adj[x][p2] && f(p,p2,1)){
            vec &t = obj[p][x][turn_left];
            t.p = p;
            t.x = p2;
            t.t = 1;
            return dp[p][x][turn_left] = 1;
        }
        return dp[p][x][turn_left] = 0;
    }
    else{
        if(norm(p-x) == 1) return 1;
        int p1 = norm(x+1), p2 = norm(p-1);
        if(adj[x][p1] && f(p,p1,0)){
            vec &t = obj[p][x][turn_left];
            t.p = p;
            t.x = p1;
            t.t = 0;
            return dp[p][x][turn_left] = 1;
        }
        if(adj[x][p2] && f(x,p2,1)){
            vec &t = obj[p][x][turn_left];
            t.p = x;
            t.x = p2;
            t.t = 1;
            return dp[p][x][turn_left] = 1;
        }
        return dp[p][x][turn_left] = 0;
    }
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    int t;
    scanf("%d",&t);
    while (t--) {
        int x,y;
        scanf("%d %d",&x,&y);
        adj[x][y] = adj[y][x] = 1;
    }
    for (int i=1; i<=n; i++) {
        if(adj[i][norm(i+1)] && f(i,norm(i+1),0)){
            int p = i, q = norm(i+1), r = 0;
            printf("%d\n",i);
            for (int j=1; j<n; j++) {
                printf("%d\n",q);
                vec t = obj[p][q][r];
                p = t.p;
                q = t.x;
                r = t.t;
            }
            return 0;
        }
        else if(adj[i][norm(i-1)] && f(i,norm(i-1),1)){
            int p = i, q = norm(i-1), r = 1;
            printf("%d\n",i);
            for (int j=1; j<n; j++) {
                printf("%d\n",q);
                vec t = obj[p][q][r];
                p = t.p;
                q = t.x;
                r = t.t;
            }
            return 0;
        }
    }
    puts("-1");
}

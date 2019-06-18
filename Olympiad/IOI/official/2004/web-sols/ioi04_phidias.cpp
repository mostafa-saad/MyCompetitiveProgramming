#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int w[201],h[201],n,dp[605][605];
 
int f(int x, int y){
    if(~dp[x][y]) return dp[x][y];
    int res = x * y;
    for (int i=0; i<n; i++) {
        if(x >= w[i] && y >= h[i]){
            res = min(res,f(x-w[i],h[i]) + f(x,y-h[i]));
            res = min(res,f(x-w[i],y) + f(w[i],y - h[i]));
        }
    }
    return dp[x][y] = res;
}
 
int main(){
    int wp,hp;
    memset(dp,-1,sizeof(dp));
    scanf("%d %d %d",&wp,&hp,&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&w[i],&h[i]);
    }
    printf("%d",f(wp,hp));
}
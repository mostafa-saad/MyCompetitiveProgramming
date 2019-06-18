#include <cstdio>
#include <algorithm>
using namespace std;
 
int main(){
    int q,m,k;
    int mn[2005], kn[2005];
    int dp[2][150005] ={};
    scanf("%d %d %d",&q,&m,&k);
    for (int i=0; i<m; i++) {
        scanf("%d",&mn[i]);
    }
    for (int i=0; i<k; i++) {
        scanf("%d",&kn[i]);
    }
    sort(kn,kn+k);
    int p = 0;
    for (int i=k-1; i>=0; i--) {
        for (int j=p; j<p+kn[i] && j <= q; j++) {
            dp[m&1][j] = max(0,j-(k-i));
        }
        p += kn[i];
    }
    for (int i=m-1; i>=0; i--) {
        for (int j=0; j<=q; j++) {
            if(j >= mn[i]) dp[i&1][j] = dp[(i+1)&1][j-mn[i]] + mn[i];
            else dp[i&1][j] = j-1;
            dp[i&1][j] = max(dp[(i+1)&1][j],dp[i&1][j]);
        }
    }
    printf("%d",dp[0][q]);
}
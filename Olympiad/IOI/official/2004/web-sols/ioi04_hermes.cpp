#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n,x[20005],y[20005];
 
int dp[2][2][2005];
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
        x[i] += 1000;
        y[i] += 1000;
    }
    for (int i=n-2; i>=0; i--) {
        for (int j=0; j<2; j++) {
            for (int k=0; k<=2000; k++) {
                int px,py;
                if(j == 0) px = k, py = y[i];
                else py = k, px = x[i];
                int ret1 = dp[(i+1)&1][0][px] + abs(py - y[i+1]);
                int ret2 = dp[(i+1)&1][1][py] + abs(px - x[i+1]);
                dp[i&1][j][k] = min(ret1,ret2);
            }
        }
    }
    printf("%d",min(dp[0][0][1000] + abs(y[0]-1000),dp[0][1][1000] + abs(x[0]-1000)));
     
}
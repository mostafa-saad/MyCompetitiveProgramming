#include <cstdio>
#include <algorithm>
using namespace std;
 
 
int main(){
    int n,m;
    char str[1000005];
    int dp[2][5][5][2] = {};
    scanf("%d %d %s",&n,&m,str);
    for (int j=0; j<5; j++) {
        for (int k=0; k<5; k++) {
            for (int l=0; l<2; l++) {
                dp[n&1][j][k][l] = 1;
            }
        }
    }
    for (int i=n-1; i>=0; i--) {
        for (int j=0; j<5; j++) {
            for (int k=0; k<5; k++) {
                for (int l=0; l<2; l++) {
                    if(str[i] == 'L' && !l){
                        if(k == 4) continue;
                        dp[i&1][j][k][l] = dp[(i+1)&1][min(2,j+1)][max(3,k+1)][l];
                    }
                    else{
                        dp[i&1][j][k][l] = 0;
                        if(k != 4){
                            dp[i&1][j][k][l] += dp[(i+1)&1][min(2,j+1)][max(3,k+1)][1];
                        }
                        if(j != 0){
                            dp[i&1][j][k][l] += dp[(i+1)&1][min(1,j-1)][max(2,k-1)][l];
                        }
                        dp[i&1][j][k][l] %= m;
                    }
                }
            }
        }
    }
    printf("%d",dp[0][2][2][0]);
}

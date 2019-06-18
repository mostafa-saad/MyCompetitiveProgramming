#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
  
int n,m;
int a[51][51];
int isum[51];
int dp[51][51][51][51];
  
int f(int xs, int xe, int ys, int ye){
    if(xs == xe && ys == ye) return 0;
    if(dp[xs][xe][ys][ye]) return dp[xs][xe][ys][ye];
    int res = 1e9;
    for (int i=xs; i<xe; i++) {
        res = min(res,f(xs,i,ys,ye)+f(i+1,xe,ys,ye));
    }
    for (int i=ys; i<ye; i++) {
        res = min(res,f(xs,xe,ys,i) + f(xs,xe,i+1,ye));
    }
    return dp[xs][xe][ys][ye] = res + a[xe][ye] - a[xs-1][ye] - a[xe][ys-1] + a[xs-1][ys-1];
}
  
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d",&a[i][j]);
            a[i][j] += a[i][j-1] + a[i-1][j] - a[i-1][j-1];
        }
    }
    printf("%d",f(1,n,1,m));
}

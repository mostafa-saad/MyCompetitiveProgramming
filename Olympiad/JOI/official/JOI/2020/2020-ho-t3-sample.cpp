#include <iostream>
#include <algorithm>
using namespace std;

template<class T> T &chmin(T &a,const T &b){ return a = min(a,b); }
template<class T> T &chmax(T &a,const T &b){ return a = max(a,b); }

using ll = long long;
const ll INF = 1e18;

ll dp[210][210][2][210];

signed main(){
    int n;
    ll l,x[210] = {},t[210];
    cin >> n >> l;
    for(int i = 0;i < n;i++) cin >> x[i + 1];
    for(int i = 0;i < n;i++) cin >> t[i + 1];
    x[n + 1] = l;
    for(int i = 0;i <= n + 1;i++){
        for(int j = 0;j <= n + 1;j++){
            for(int k = 0;k < 2;k++){
                for(int m = 0;m <= n;m++) dp[i][j][k][m] = INF;
            }
        }
    }
    dp[0][n + 1][0][0] = dp[0][n + 1][1][0] = 0;
    for(int i = 0;i < n;i++){
        for(int j = n + 1;j >= i + 2;j--){
            for(int m = 0;m <= n;m++){
                ll tim = min(dp[i][j][0][m]+x[i+1]-x[i],dp[i][j][1][m]+l-x[j]+x[i+1]);
                chmin(dp[i + 1][j][0][m + (tim <= t[i + 1])],tim);
                tim = min(dp[i][j][0][m]+l-x[j-1]+x[i],dp[i][j][1][m]+x[j]-x[j-1]);
                chmin(dp[i][j - 1][1][m + (tim <= t[j - 1])],tim);
            }
        }
    }
    int ans = 0;
    for(int i = 0;i <= n + 1;i++){
        for(int j = 0;j <= n + 1;j++){
            for(int k = 0;k < 2;k++){
                for(int m = 0;m <= n;m++){
                    if(dp[i][j][k][m] != INF) chmax(ans,m);
                }
            }
        }
    }
    cout << ans << endl;
}
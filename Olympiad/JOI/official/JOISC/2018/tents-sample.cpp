#include<cstdio>
#include<algorithm>

using namespace std;

const long long mod = 1000000007;

const int MAX_N = 3000;

long long dp[MAX_N + 1][MAX_N + 1];

int H, W;

long long C2(int x){
	return x * (x - 1) / 2;
}

long long solve(){
	for(int i = 0; i <= H; ++i){
		for(int j = 0; j <= W; ++j){
			if(i == 0 || j == 0){
				dp[i][j] = 1;
			}else{
				dp[i][j] = 0;
				dp[i][j] += dp[i][j - 1];
				dp[i][j] += 4ll * i * dp[i - 1][j - 1];
				if(i >= 2){
					long long tmp = C2(i);
					dp[i][j] += tmp * dp[i - 2][j - 1];
				}
				if(j >= 2){
					dp[i][j] += (long long)i * (j - 1) * dp[i - 1][j - 2];
				}
				dp[i][j] %= mod;
			}
		}
	}
	long long ans = dp[H][W] - 1;
	ans %= mod;
	ans += mod;
	ans %= mod;
	return ans;
}

int main(){
	scanf("%d%d", &H, &W);
	long long ans = solve();
	printf("%lld\n", ans);
	return 0;
}

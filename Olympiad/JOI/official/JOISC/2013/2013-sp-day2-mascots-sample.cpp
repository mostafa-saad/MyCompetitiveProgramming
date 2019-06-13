#include <cstdio>

int MOD=1000000007;
int R,C,N;
int r1,r2,c1,c2;
long long fact[12000001];
long long dp[3002][3002];
long long comb[3001][3001];
int main() {
	scanf("%d%d%d",&R,&C,&N);
	r1=R; c1=C;
	for(int i=0;i<N;i++) {
		int kr,kc;
		scanf("%d%d",&kr,&kc);
		if(r1>kr) r1=kr;
		if(r2<kr) r2=kr;
		if(c1>kc) c1=kc;
		if(c2<kc) c2=kc;
	}
	fact[0]=1;
	for(int i=1;i<12000001;i++) fact[i]=(fact[i-1]*i)%MOD;
	comb[0][0]=1;
	for(int i=1;i<3001;i++) {
		comb[i][0]=comb[i-1][0];
		for(int j=1;j<=i;j++) {
			comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%MOD;
		}
	}
	dp[0][0]=fact[(r2-r1+1)*(c2-c1+1)-N];
	for(int i=0;i<=R-(r2-r1+1);i++) {
		for(int j=0;j<=C-(c2-c1+1);j++) {
			dp[i+1][j]=(dp[i+1][j]+dp[i][j]*fact[C-j])%MOD;
			dp[i][j+1]=(dp[i][j+1]+dp[i][j]*fact[R-i])%MOD;
		}
	}
	long long sol=dp[R-(r2-r1+1)][C-(c2-c1+1)];
	sol=(sol*comb[R-(r2-r1+1)][r1-1])%MOD;
	sol=(sol*comb[C-(c2-c1+1)][c1-1])%MOD;
	printf("%lld\n",sol);
	return 0;
}

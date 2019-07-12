#include <cstdio>

int N,M;
int pos[100008];
int level[100008];
int def_level[100008];
int dp[300008];
const int INF=1000000007;
int firsttwo(int va,int vb,int vc) {
	//return min plus median
	if(va>=vb&&va>=vc) return vb+vc;
	if(vb>=va&&vb>=vc) return va+vc;
	return va+vb;
}
int check(int K) {
	// more than or equal to K
	int dancers=0;
	for(int i=M+1;i<=N;i++) if(level[i]>=K) dancers++;
	//dp[1], dp[2], ... , dp[N]
	for(int i=1;i<=N;i++) {
		if(def_level[i]==-1) {
			dp[i]=1;
		} else {
			if(def_level[i]>=K) {
				dp[i]=0;
			} else {
				dp[i]=INF;
			}
		}
	}
	int left=1;
	int right=N;
	//dp[N+1], dp[N+2], ...
	while(left<right) {
		dp[right+1]=firsttwo(dp[left],dp[left+1],dp[left+2]);
		if(dp[right+1]>INF) dp[right+1]=INF;
		right++;
		left+=3;
	}
	if(dp[left]<=dancers) return 1;
	return 0;
}
int main() {
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++) def_level[i]=-1;
	for(int i=1;i<=M;i++) {
		scanf("%d%d",&level[i],&pos[i]);
		def_level[pos[i]]=level[i];
	}
	for(int i=M+1;i<=N;i++) scanf("%d",&level[i]);
	int minv=1;
	int maxv=1000000000;
	// binary search main part
	while(minv<maxv) {
		int hf=(minv+maxv+1)/2;
		if(check(hf)==1) {
			minv=hf;
		} else {
			maxv=hf-1;
		}
	}
	printf("%d\n",minv);
	return 0;
}

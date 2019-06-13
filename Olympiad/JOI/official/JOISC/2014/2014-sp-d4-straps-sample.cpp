#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 2010;

int N, A[MAXN], B[MAXN], dp[MAXN][2*MAXN+1];

int main()
{
	scanf("%d", &N);
	for(int i=0;i<N;i++) scanf("%d%d", A+i, B+i);

	for(int i=0;i<=2*MAXN;i++) dp[0][i] = -2100000000;
	dp[0][MAXN+1] = 0;

	for(int i=0;i<N;i++){
		for(int j=0;j<=2*MAXN;j++) dp[i+1][j] = -2100000000;

		for(int j=0;j<=2*MAXN;j++){
			int j2 = j + (A[i] - 1);
			if(j2 < 0) continue;
			if(j2 > 2*MAXN) j2 = 2*MAXN;

			dp[i+1][j2] = max(dp[i+1][j2], dp[i][j] + B[i]);
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
		}
	}

	int ret = 0;
	for(int i=MAXN;i<=2*MAXN;i++) ret = max(ret, dp[N][i]);

	printf("%d\n", ret);

	return 0;
}

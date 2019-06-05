#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
long long mod=1000000007;
int c[110];
long long dp[110][110][1100][3];
int main(){
	int a,b;scanf("%d%d",&a,&b);
	for(int i=0;i<a;i++)scanf("%d",c+i);
	std::sort(c,c+a);
	if(a==1){
		printf("1\n");return 0;
	}
	c[a]=9999;
	if(c[1]-c[0]<=b)dp[1][1][c[1]-c[0]][1]=2;
	if((c[1]-c[0])*2<=b)dp[1][1][2*(c[1]-c[0])][0]=1;
	
	for(int i=1;i<a;i++){
		int ad=c[i+1]-c[i];
	//	printf("(%d)\n",ad);
		for(int j=0;j<=i;j++)for(int k=0;k<=b;k++)for(int l=0;l<3;l++){
			if(!dp[i][j][k][l])continue;
		//	printf("%d %d %d %d: %lld\n",i,j,k,l,dp[i][j][k][l]);
			if(l<2&&k+ad*(2*j-l-1)<=b){
			//	printf("%d\n",2*j-l-1);
				if(i==a-1)dp[i+1][j][k+ad*(2*j-l-1)][l+1]=(dp[i+1][j][k+ad*(2*j-l-1)][l+1]+dp[i][j][k][l]*(2-l)*j)%mod;
				else if(l==0||j>1)dp[i+1][j][k+ad*(2*j-l-1)][l+1]=(dp[i+1][j][k+ad*(2*j-l-1)][l+1]+dp[i][j][k][l]*(2-l)*(j-l))%mod;
				if(k+ad*(2*j-l+1)<=b){
					dp[i+1][j+1][k+ad*(2*j-l+1)][l+1]=(dp[i+1][j+1][k+ad*(2*j-l+1)][l+1]+dp[i][j][k][l]*(2-l))%mod;
				}
			}
	//		printf("%d\n",2*j-l);
			if(k+ad*(2*j-l+2)<=b)dp[i+1][j+1][k+ad*(2*j-l+2)][l]=(dp[i+1][j+1][k+ad*(2*j-l+2)][l]+dp[i][j][k][l])%mod;
			if(k+ad*(2*j-l)<=b)dp[i+1][j][k+ad*(2*j-l)][l]=(dp[i+1][j][k+ad*(2*j-l)][l]+dp[i][j][k][l]*(2*j-l))%mod;
			if(j>=2&&k+ad*(2*j-2-l)<=b&&(i==a-1||j>2||l<2)){
	//			printf("%d\n",2*j-2-l);
				if(l==0)dp[i+1][j-1][k+ad*(2*j-2-l)][l]=(dp[i+1][j-1][k+ad*(2*j-2-l)][l]+dp[i][j][k][l]*j*(j-1))%mod;
				if(l==1)dp[i+1][j-1][k+ad*(2*j-2-l)][l]=(dp[i+1][j-1][k+ad*(2*j-2-l)][l]+dp[i][j][k][l]*(j-1)*(j-1))%mod;
				if(l==2){
					if(i<a-1)dp[i+1][j-1][k+ad*(2*j-2-l)][l]=(dp[i+1][j-1][k+ad*(2*j-2-l)][l]+dp[i][j][k][l]*((j-2)*(j-2)+j-2))%mod;	
					else dp[i+1][j-1][k+ad*(2*j-2-l)][l]=(dp[i+1][j-1][k+ad*(2*j-2-l)][l]+dp[i][j][k][l]*((j-2)*(j-2)+j-1))%mod;	
				}
			}
		}
	}
	//for(int i=0;i<=a;i++)for(int j=0;j<=b;j++)for(int k=0;k<3;k++)if(dp[a][i][j][k])printf("%d %d %d: %lld\n",i,j,k,dp[a][i][j][k]);
	long long ret=0;
	for(int i=0;i<=b;i++)ret=(ret+dp[a][1][i][2])%mod;
	printf("%lld\n",ret);
}
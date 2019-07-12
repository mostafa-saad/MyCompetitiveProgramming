#include<stdio.h>
#include<algorithm>
using namespace std;
long long dp[2100][2100];
int b[2100];
int a;
long long calc(int l,int r,int s){
	if(~dp[l][r])return dp[l][r];
	if(l==r){
		if(s)return dp[l][r]=0;
		return dp[l][r]=b[l];
	}
	if(s){
		if(b[l]>b[r]){
			return dp[l][r]=calc((l+1)%a,r,0);
		}else{
			return dp[l][r]=calc(l,(r+a-1)%a,0);
		}
	}
	return dp[l][r]=max(calc((l+1)%a,r,1)+b[l],calc(l,(r+a-1)%a,1)+b[r]);
}
int main(){
	scanf("%d",&a);
	for(int i=0;i<a;i++)scanf("%d",b+i);
	for(int i=0;i<2100;i++)for(int j=0;j<2100;j++)
		dp[i][j]=-1;
	long long ret=0;
	for(int i=0;i<a;i++){
		ret=max(ret,calc((i+1)%a,(i+a-1)%a,1)+b[i]);
	}
	printf("%lld\n",ret);
}
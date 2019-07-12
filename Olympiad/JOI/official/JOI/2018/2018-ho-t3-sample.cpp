#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<queue>
#include<deque>
#include<string>
#include<string.h>
#include<vector>
#include<set>
#include<map>
#include<stdlib.h>
#include<cassert>
using namespace std;
const long long mod=1000000009;
const long long inf=mod*mod;
const long long d2=500000004;
const double EPS=1e-10;
const double PI=acos(-1.0);
int ABS(int a){return max(a,-a);}
long long ABS(long long a){return max(a,-a);}
char str[3100][3100];
char p[3][3100];
int dp[3100][3];
int main(){
	int a,b;scanf("%d%d",&a,&b);
	for(int i=0;i<a;i++)scanf("%s",str[i]);
	int ret=0;
	for(int i=1;i<a+b-2;i++){
		for(int j=0;j<3;j++)for(int k=0;k<3100;k++)p[j][k]='.';
		for(int j=0;j<3;j++){
			for(int k=0;k<b;k++){
				int r=i+j-1-k;
				int c=k;
				if(r<0||r>=a)continue;
				p[j][k]=str[r][c];
			}
		}
		for(int j=0;j<3;j++)for(int k=0;k<3100;k++)dp[k][j]=0;
		for(int j=0;j<b;j++){
			for(int k=0;k<3;k++){
				dp[j+1][0]=max(dp[j+1][0],dp[j][k]);
				if(p[1][j]!='G')continue;
				if(j&&k!=1&&p[0][j-1]=='R'&&p[2][j+1]=='W')dp[j+1][2]=max(dp[j+1][2],dp[j][k]+1);
				if(k!=2&&p[0][j]=='R'&&p[2][j]=='W')dp[j+1][1]=max(dp[j+1][1],dp[j][k]+1);
			}
		}
		ret+=max(max(dp[b][0],dp[b][1]),dp[b][2]);
	}
	printf("%d\n",ret);
}
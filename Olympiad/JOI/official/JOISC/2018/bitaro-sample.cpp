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
#include<time.h>
#include<bitset>
using namespace std;
const long long mod=1000000007;
const long long inf=mod*mod;
const long long d2=500000004;
const double EPS=1e-6;
const double PI=acos(-1.0);
int ABS(int a){return max(a,-a);}
long long ABS(long long a){return max(a,-a);}
vector<int>g[110000];
vector<int>rev[110000];
int at[110000][320];
int dist[110000][320];
const int SQ=320;
int tmp_a[330];
int tmp_b[330];
int use[110000];
int z[110000];
int dp[110000];
int main(){
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	for(int i=0;i<b;i++){
		int p,q;scanf("%d%d",&p,&q);p--;q--;
		g[p].push_back(q);
		rev[q].push_back(p);
	}
	for(int i=0;i<a;i++)for(int j=0;j<320;j++)
		dist[i][j]=-mod;
	for(int i=0;i<a;i++){
		dist[i][0]=0;
		at[i][0]=i;
	}
	for(int i=0;i<a;i++){
		for(int j=0;j<g[i].size();j++){
			int to=g[i][j];
			int left=0;
			int right=0;
			int sz=0;
			while(left<SQ||right<SQ){
				if(sz==SQ)break;
				int S,T;
				if((left==SQ||dist[i][left]<0)&&(right==SQ||dist[to][right]<0))break;
				if(right==SQ||(left<SQ&&dist[i][left]+1>=dist[to][right])){
					S=at[i][left];
					T=dist[i][left]+1;
					left++;
				}else{
					S=at[to][right];
					T=dist[to][right];
					right++;
				}
				if(!use[S]){
					tmp_a[sz]=S;
					tmp_b[sz]=T;
					use[S]=1;
					sz++;
				}
			}
			for(int k=0;k<sz;k++)dist[to][k]=tmp_b[k];
			for(int k=0;k<sz;k++)at[to][k]=tmp_a[k];
			for(int k=0;k<sz;k++)use[tmp_a[k]]=0;
		}
	}

	for(int i=0;i<c;i++){
		int x,y;scanf("%d%d",&x,&y);
		x--;
		for(int j=0;j<y;j++){
			scanf("%d",z+j);
			z[j]--;
		}
		for(int j=0;j<y;j++){
			use[z[j]]=1;
		}
		if(y<SQ){
			bool ok=false;
			for(int j=0;j<SQ;j++){
				if(dist[x][j]<0)break;
				if(!use[at[x][j]]){
					ok=true;
					printf("%d\n",dist[x][j]);
					break;
				}
			}
			if(!ok)printf("-1\n");
		}else{
			for(int j=0;j<a;j++){
				dp[j]=-mod;
			}
			dp[x]=0;
			for(int j=x;j>=0;j--){
				for(int k=0;k<rev[j].size();k++){
					dp[rev[j][k]]=max(dp[rev[j][k]],dp[j]+1);
				}
			}
			int ret=-1;
			for(int j=0;j<a;j++){
				if(!use[j])ret=max(ret,dp[j]);
			}
			printf("%d\n",ret);
		}
		for(int j=0;j<y;j++){
			use[z[j]]=0;
		}
	}
}
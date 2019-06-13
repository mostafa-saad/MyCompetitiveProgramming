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
using namespace std;
const long long mod=1000000007;
const long long inf=mod*mod;
const long long d2=500000004;
int p[110000];
int q[110000];
int A[110000];
int B[110000];

int v1[110000][20];
int w1[110000][20];
int v2[110000][20];
int w2[110000][20];
int N,M;
map<pair<pair<int,int>,int>,long long> dp;
long long dfs(int a,int b,int c){
	//printf("%d %d %d\n",a,b,c);
	if(dp.count(make_pair(make_pair(a,b),c)))return dp[make_pair(make_pair(a,b),c)];
	pair<pair<int,int>,int> pos=make_pair(make_pair(a,b),c);
	int num;
	if(c<2)num=p[a];
	else num=q[b];
	if(c==0){
		int at=b+1;
		for(int i=19;i>=0;i--){
			if(at>101000)break;
			if(w1[at][i]<num){
				at+=(1<<i);
			}
		}
		if(at>=M){
			return dp[pos]=M-1-b;
		}else{
			return dp[pos]=max(dfs(a,at,2),dfs(a,at,3))+at-b;
		}
	}else if(c==1){
		int at=b-1;
		at=M-1-at;
		for(int i=19;i>=0;i--){
			if(at>101000)break;
			if(w2[at][i]<num){
				at+=(1<<i);
			}
		}
		if(at>=M){
			return dp[pos]=b;
		}else{
			at=M-1-at;
			return dp[pos]=max(dfs(a,at,2),dfs(a,at,3))+b-at;
		}
	}else if(c==2){
		int at=a+1;
		for(int i=19;i>=0;i--){
			if(at>101000)break;
			if(v1[at][i]<num){
				at+=(1<<i);
			}
		}
		if(at>=N){
			return dp[pos]=N-1-a;
		}else{
			return dp[pos]=max(dfs(at,b,0),dfs(at,b,1))+at-a;
		}
	}else{
		int at=a-1;
		at=N-1-at;
		for(int i=19;i>=0;i--){
			if(at>101000)break;
			if(v2[at][i]<num){
				at+=(1<<i);
			}
		}
		if(at>=N){
			return dp[pos]=a;
		}else{
			at=N-1-at;
			return dp[pos]=max(dfs(at,b,0),dfs(at,b,1))+a-at;
		}
	}
//	return dp[make_pair(make_pair(a,b),c)]=ret;
}
int main(){
	int a,b,c;scanf("%d%d%d",&a,&b,&c);
	N=a;M=b;
	for(int i=0;i<a;i++)scanf("%d",p+i);
	for(int i=0;i<b;i++)scanf("%d",q+i);
	for(int i=0;i<c;i++){
		scanf("%d%d",A+i,B+i);
		A[i]--;B[i]--;
	}
	for(int i=0;i<a;i++){
		v1[i][0]=p[i];
	}
	for(int i=0;i<b;i++){
		w1[i][0]=q[i];
	}
	for(int i=1;i<20;i++){
		for(int j=0;j<a;j++){
			v1[j][i]=max(v1[j][i-1],v1[min(101000,j+(1<<(i-1)))][i-1]);
		}
		for(int j=0;j<b;j++){
			w1[j][i]=max(w1[j][i-1],w1[min(101000,j+(1<<(i-1)))][i-1]);
		}
	}

	for(int i=0;i<a;i++){
		v2[i][0]=p[a-1-i];
	}
	for(int i=0;i<b;i++){
		w2[i][0]=q[b-1-i];
	}
	for(int i=1;i<20;i++){
		for(int j=0;j<a;j++){
			v2[j][i]=max(v2[j][i-1],v2[min(101000,j+(1<<(i-1)))][i-1]);
		}
		for(int j=0;j<b;j++){
			w2[j][i]=max(w2[j][i-1],w2[min(101000,j+(1<<(i-1)))][i-1]);
		}
	}
	for(int i=0;i<c;i++){
		long long ret=0;
		for(int j=0;j<4;j++){
		//	printf("%d %d %d: %lld\n",A[i],B[i],j,dfs(A[i],B[i],j));
			ret=max(ret,dfs(A[i],B[i],j));
		}
		printf("%lld\n",ret);
	}
}

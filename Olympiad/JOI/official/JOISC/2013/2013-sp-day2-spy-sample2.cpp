#include <cstdio>
#include <algorithm>
#define MAXN 2000
#define MAXN2 4000
#define MAXM 500000
using namespace std;
int N,M;
int Pa,Qa;
int Rb,Sb;
int parenti[MAXN];
int parentj[MAXN];
int shachoi;
int shachoj;
int cnt[MAXN][MAXN];
int memo[MAXN][MAXN];

int memo_dp(int j,int i){
	if(memo[j][i]!=-1){return memo[j][i];}
	memo[j][i]=cnt[j][i];
	if(j!=shachoj){memo[j][i]+=memo_dp(parentj[j],i);}
	if(i!=shachoi){memo[j][i]+=memo_dp(j,parenti[i]);}
	if(j!=shachoj&&i!=shachoi){memo[j][i]-=memo_dp(parentj[j],parenti[i]);}
	return memo[j][i];
}
int main(){
	scanf("%d %d\n",&N,&M);
	for(int a=0;a<N;a++){
		scanf("%d %d\n",&Pa,&Qa);
		if(Pa!=0){
			Pa--;
			parentj[a]=Pa;
		}else{shachoj=a;}
		if(Qa!=0){
			Qa--;
			parenti[a]=Qa;
		}else{shachoi=a;}
		fill(memo[a],memo[a]+N,-1);
	}
	for(int b=0;b<M;b++){
		scanf("%d %d",&Rb,&Sb);
		Rb--;Sb--;
		cnt[Rb][Sb]+=1;
	}
	
	for(int i=0;i<N;i++){
		printf("%d\n",memo_dp(i,i));
	}
	
}
#include<cstdio>
#include<algorithm>

using namespace std;

const int MAX_N = 100000;
const int MAX_M = 100000;
int cnt[MAX_N+1];
int A[MAX_N],B[MAX_N],C[MAX_N];

int P[MAX_M];

int N,M;

int main(){
	scanf("%d%d",&N,&M);
	for(int i=0;i<M;i++){
		scanf("%d",P+i);
	}
	for(int i=0;i<N-1;i++){
		scanf("%d%d%d",A+i,B+i,C+i);
	}
	for(int i=0;i<M-1;i++){
		int x=P[i],y=P[i+1];
		if(x>y) swap(x,y);
		x--;
		y--;
		cnt[x]++;
		cnt[y]--;
	}
	for(int i=1;i<N;i++){
		cnt[i]+=cnt[i-1];
	}
	long long ans=0;
	for(int i=0;i<N-1;i++){
		long long paper=(long long)A[i]*cnt[i];
		long long ic=(long long)B[i]*cnt[i]+C[i];
		ans+=min(paper,ic);
	}
	printf("%lld\n",ans);
	return 0;
}

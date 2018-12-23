// O(n(log^2)n) solution. Should not get the full score!!!
// Author: Dawid Dabrowski

#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN=1000005;
const int M=1<<20;
const int INF=1000000000;

int n;
pair<int,int> a[MAXN];

pair<int,int> tree[2*M];

void add(int u,int x) {
	u+=M;
	tree[u]=make_pair(x,u-M);
	while(u/2) {
		u/=2;
		tree[u]=max(tree[2*u],tree[2*u+1]);
	}
}

pair<int,int> get(int a,int b) {
	if(b<a) return make_pair(-INF,-1);
	a+=M; b+=M;
	pair<int,int> res=max(tree[a],tree[b]);
	while(a/2 != b/2) {
		if(!(a&1)) res=max(res,tree[a+1]);
		if(b&1) res=max(res,tree[b-1]);
		a/=2; b/=2;
	}
	return res;
}

void clear() {
	for(int i=0; i<2*M; ++i) tree[i]=make_pair(-INF,-1);
}

int grsize[MAXN];

int calc(int limit) {
	//printf("calc %d\n",limit);
	clear();
	for(int i=0; i<n; ++i) {
		//printf("i = %d\n",i);
		int r=i-a[i].first,l=i-limit;
		l=max(l,0);
		pair<int,int> p=get(l,r);
		//printf("get %d %d = %d\n",l,r,p.first);
		if(p.first!=-INF) {
			grsize[i]=i-p.second;
			add(i,p.first+1);
		} else if(i+1>=a[i].first && (i+1)<=limit) {
			grsize[i]=i+1;
			add(i,1);
		} else {
			grsize[i]=-1;
		}
//		printf("dp[%d] = %d   %d            grsize = %d\n",i,tree[i+M].first,tree[i+M].second,grsize[i]);
	}
	return tree[n-1+M].first;
}

int main() {
	scanf("%d",&n);
	for(int i=0; i<n; ++i) {
		scanf("%d",&a[i].first);
		a[i].second=i;
	}
	sort(a,a+n);
	int best=calc(n);
	//printf("best = %d\n",best);
	int l=1,u=n,r=-1;
	while(l<=u) {
		int m=(l+u)/2;
		int cur=calc(m);
		if(cur==best) {
			r=m;
			u=m-1;
		} else l=m+1;
	}
	calc(r);
	//printf("r=%d\n",r);
	printf("%d\n",best);
	for(int i=n-1; i>=0; i-=grsize[i]) {
		printf("%d",grsize[i]);
		for(int j=i; j>i-grsize[i]; --j) printf(" %d",a[j].second+1);
		printf("\n");
	}
	return 0;
}

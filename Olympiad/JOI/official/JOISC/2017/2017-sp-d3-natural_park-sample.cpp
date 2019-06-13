#include <stdio.h>
#include "park.h"

static int Place[9999];
static int checked[9999]; //0:not 1:checked 2:in_stack
static int edges[9999][9];
static int degree[9999];
static int N;
static int myAsk(int A,int B) {
	if(A>B) return myAsk(B,A);
	return Ask(A,B,Place);
}
static void myAnswer(int A,int B) {
	if(A>B) {
		Answer(B,A);
	} else {
		Answer(A,B);
	}
	edges[A][degree[A]++]=B;
	edges[B][degree[B]++]=A;
}
static int direct_connection(int now) {
	int i;
	for(i=0;i<N;i++) {
		Place[i]=0;
		if(checked[i]==1) Place[i]=1;
	}
	Place[now]=1;
	return myAsk(0,now);
}
static int find_new_node(int now) {
	int i;
	int minv=0; int maxv=N-1;
	while(minv<maxv) {
		int hf=(minv+maxv)/2;
		for(i=0;i<N;i++) Place[i]=0;
		for(i=0;i<=hf;i++) if(checked[i]!=2) Place[i]=1;
		for(i=hf+1;i<N;i++) if(checked[i]==1) Place[i]=1;
		Place[now]=1;
		if(myAsk(0,now)) {
			maxv=hf;
		} else {
			minv=hf+1;
		}
	}
	return minv;
}
static int rem[9999];
static int dfs_order_size;
static int dfs_order[9999];
static int dfs_order_checked[9999];
static void dfs_order_calc(int now) {
	dfs_order_checked[now]=1;
	dfs_order[dfs_order_size++]=now;
	int i;
	for(i=0;i<degree[now];i++) if(rem[edges[now][i]]==1&&dfs_order_checked[edges[now][i]]==0) dfs_order_calc(edges[now][i]);
}
static void dfs_delete(int now) {
	rem[now]=0;
	Place[now]=0;
	int i;
	for(i=0;i<degree[now];i++) if(rem[edges[now][i]]==1) dfs_delete(edges[now][i]);
}
static void find_edges(int now) {
	int cur,i;
	for(i=0;i<N;i++) rem[i]=0;
	for(i=0;i<N;i++) if(checked[i]==1) rem[i]=1;
	for(cur=0;cur<N;cur++) {
		while(rem[cur]) {
			for(i=0;i<N;i++) Place[i]=rem[i];
			Place[now]=1;
			if(myAsk(cur,now)) {
				dfs_order_size=0;
				for(i=0;i<N;i++) dfs_order_checked[i]=0;
				dfs_order_calc(cur);
				int minv=0; int maxv=dfs_order_size-1;
				while(minv<maxv) {
					int hf=(minv+maxv)/2;
					for(i=0;i<=hf;i++) Place[dfs_order[i]]=1;
					for(i=hf+1;i<dfs_order_size;i++) Place[dfs_order[i]]=0;
					if(myAsk(cur,now)==0) {
						minv=hf+1;
					} else {
						maxv=hf;
					}
				}
				myAnswer(now,dfs_order[minv]);
				rem[dfs_order[minv]]=0;
				Place[dfs_order[minv]]=0;
			} else {
				dfs_delete(cur);
			}
		}
	}
}
static void execute(int now) {
	checked[now]=2;
	while(direct_connection(now)==0) {
		int next=find_new_node(now);
		execute(next);
	}
	find_edges(now);
	checked[now]=1;
}
void Detect(int T,int N_get) {
	N=N_get;
	int i;
	checked[0]=1;
	for(i=1;i<N;i++) if(checked[i]==0) execute(i);
}

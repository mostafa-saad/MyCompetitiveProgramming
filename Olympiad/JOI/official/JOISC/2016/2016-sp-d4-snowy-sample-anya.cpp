#include "Anyalib.h"

static int getN;
static int getA[9999];
static int getB[9999];
static int getC[9999];
static int depth[9999];
static int parent[9999];
static int depthsum[99];
static int mindepth=0;
static int index[9999];
static void dfs(int now,int from,int curdepth) {
	depth[now]=curdepth;
	depthsum[curdepth%10]++;
	parent[now]=from;
	for(int i=0;i<getN-1;i++) {
		if(getA[i]==now) {
			if(getB[i]!=from) {
				dfs(getB[i],now,curdepth+1);
			}
		}
		if(getB[i]==now) {
			if(getA[i]!=from) {
				dfs(getA[i],now,curdepth+1);
			}
		}
	}
}
static void calcmin() {
	int mindepthvalue=getN;
	int i;
	for(i=0;i<10;i++) if(mindepthvalue>depthsum[i]) {
		mindepthvalue=depthsum[i];
		mindepth=i;
	}
}
void InitAnya(int N , int A[] , int B[]) {
	getN=N;
	for(int i=0;i<N-1;i++) {
		getA[i]=A[i];
		getB[i]=B[i];
	}
	dfs(0,-1,0);
	calcmin();
	int temp=0;
	int i;
	for(i=1;i<N;i++) {
		index[i]=temp;
		if(depth[i]%10==mindepth) {
			temp+=9;
		} else {
			temp++;
		}
	}
}
static void dfs2(int now,int from,int curdepth,int cursum,int prev) {
	if(now) {
		if(curdepth%10==mindepth) {
			int i;
			for(i=0;i<9;i++) {
				if(cursum&(1<<(8-i))) {
					Save(index[now]+i,1);
				} else {
					Save(index[now]+i,0);
				}
			}
		} else {
			Save(index[now],prev);
		}
	}
	for(int i=0;i<getN-1;i++) {
		if(getA[i]==now) {
			if(getB[i]!=from) {
				dfs2(getB[i],now,curdepth+1,cursum+getC[i],getC[i]);
			}
		}
		if(getB[i]==now) {
			if(getA[i]!=from) {
				dfs2(getA[i],now,curdepth+1,cursum+getC[i],getC[i]);
			}
		}
	}
}
void Anya(int C[]) {
	int i;
	for(i=0;i<getN-1;i++) getC[i]=C[i];
	dfs2(0,-1,0,0,-1);
}

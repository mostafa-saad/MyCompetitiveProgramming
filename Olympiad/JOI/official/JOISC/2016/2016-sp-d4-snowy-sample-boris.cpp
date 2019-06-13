#include <stdio.h>
#include "Borislib.h"

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
void InitBoris(int N , int A[] , int B[]) {
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
int Boris(int city) {
	int sol=0;
	int solx=0;
	int i;
	while(depth[city]%10!=mindepth) {
		if(city==0) break;
		sol+=Ask(index[city]);
		city=parent[city];
	}
	if(city) {
		for(i=0;i<9;i++) solx = solx*2 + Ask(index[city]+i);
	}
	if(sol+solx>=getN) return getN-1;
	return sol+solx;
}

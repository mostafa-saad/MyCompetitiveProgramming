#include <cstdio>
#include <cstdlib>

int N;
int segt[2250000];
void add(int id,int lf,int rg,int plc) {
	if(lf>plc||rg<plc) return;
	if(lf==rg&&lf==plc) {
		segt[id]=1;
		return;
	}
	int hf=(lf+rg)/2;
	add(id*2+1,lf,hf,plc);
	add(id*2+2,hf+1,rg,plc);
	segt[id]=segt[id*2+1]+segt[id*2+2];
}
int calc(int id,int lf,int rg,int callf,int calrg) {
	if(lf>calrg||rg<callf) return 0;
	if(callf<=lf&&calrg>=rg) return segt[id];
	int hf=(lf+rg)/2;
	return calc(id*2+1,lf,hf,callf,calrg)+calc(id*2+2,hf+1,rg,callf,calrg);
}
typedef struct {
	int vl;
	int plc;
}plts;
plts plt[300002];
int cmp(const void *ka,const void *kb) {
	plts *a=(plts *)ka;
	plts *b=(plts *)kb;
	if(a->vl!=b->vl) return b->vl-a->vl;
	return a->plc-b->plc;
}
int getmin(int a,int b) {
	if(a>b) return b;
	return a;
}
int main() {
	scanf("%d",&N);
	for(int i=0;i<2250000;i++) segt[i]=0;
	for(int i=0;i<N;i++) {
		scanf("%d",&plt[i].vl);
		plt[i].plc=i+1;
	}
	qsort(plt,N,sizeof(plts),cmp);
	long long sol=0;
	int nw=0;
	while(nw<N) {
		int nvl=plt[nw].vl;
		int nwb=nw;
		while(nw<N) {
			if(plt[nw].vl!=nvl) break;
			sol+=getmin(calc(0,1,N,1,plt[nw].plc),calc(0,1,N,plt[nw].plc,N));
			nw++;
		}
		while(nwb<nw) {
			add(0,1,N,plt[nwb].plc);
			nwb++;
		}
	}
	printf("%lld\n",sol);
	return 0;
}

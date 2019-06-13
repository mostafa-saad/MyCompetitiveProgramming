#include <cstdio>
#include <cstdlib>

int N;
int INF=1000000007;
typedef struct {
	int x;
	int y;
}scs;
scs sc[200008];
int cmpi(const void *ka,const void *kb) {
	int a=*(int *)ka;
	int b=*(int *)kb;
	return a-b;
}
int cmp(const void *ka,const void *kb) {
	scs *a=(scs *)ka;
	scs *b=(scs *)kb;
	return b->y - a->y;
}
int sz[5000000];
int lnx[5000000];
int lny[5000000];
int bsx[200002];
int bsy[200002];
int bstx(int vl) {
	int minv=0; int maxv=N-1;
	while(minv<maxv) {
		int hf=(minv+maxv)/2;
		if(bsx[hf]<vl) {
			minv=hf+1;
		} else {
			maxv=hf;
		}
	}
	return minv;
}
int bsty(int vl) {
	int minv=0; int maxv=N-1;
	while(minv<maxv) {
		int hf=(minv+maxv)/2;
		if(bsy[hf]<vl) {
			minv=hf+1;
		} else {
			maxv=hf;
		}
	}
	return minv;
}
void addq(int id,int lf,int rg,int addx,int addy) {
	if(lf>addx||rg<addx) return;
	//printf("plc %d %d %d %d\n",addx,addy,lf,rg);
	while(sz[id]) {
		if(lnx[id+sz[id]-1]<addx) break;
		sz[id]--;
	}
	lnx[id+sz[id]]=addx;
	lny[id+sz[id]]=addy;
	sz[id]++;
	if(lf<rg) {
		int hf=(lf+rg)/2;
		addq(id+N,lf,hf,addx,addy);
		addq(id+N+hf-lf+1,hf+1,rg,addx,addy);
	}
}
long long sol=0;
int finds(int id,int vl) {
	int minv=0; int maxv=sz[id];
	while(minv<maxv) {
		int hf=(minv+maxv)/2;
		//printf("xx%d %d\n",lny[id+hf],vl);
		if(lny[id+hf]>vl) {
			minv=hf+1;
		} else {
			maxv=hf;
		}
	}
	return minv;
}
int calc(int id,int lf,int rg,int qst) {
	//返り値:右端のy座標
	if(rg<qst) return INF;
	int hf=(lf+rg)/2;
	int mashiro=id+N+hf-lf+1;
	if(qst<=hf+1) {
		int cdy=calc(id+N,lf,hf,qst);
		/*
		if(sz[mashiro]>finds(mashiro,cdy)) printf("s%d %d %d %d %d\n",mashiro,cdy,hf+1,rg,sz[mashiro]-finds(mashiro,cdy));
		*/
		sol+=sz[mashiro]-finds(mashiro,cdy);
		if(sz[mashiro]) if(lny[mashiro+sz[mashiro]-1]<cdy) return lny[mashiro+sz[mashiro]-1];
		return cdy;
	} else {
		if(lf==rg) return INF;
		return calc(mashiro,hf+1,rg,qst);
	}
}
int main() {
	scanf("%d",&N);
	for(int i=0;i<N;i++) {
		scanf("%d%d",&sc[i].x,&sc[i].y);
		bsx[i]=sc[i].x;
		bsy[i]=sc[i].y;
	}
	qsort(bsx,N,sizeof(int),cmpi);
	qsort(bsy,N,sizeof(int),cmpi);
	for(int i=0;i<N;i++) {
		sc[i].x=bstx(sc[i].x);
		sc[i].y=bsty(sc[i].y);
	}
	qsort(sc,N,sizeof(scs),cmp);
	for(int qry=0;qry<N;qry++) {
		//printf("%d %d\n",sc[qry].x,sc[qry].y);
		calc(0,0,N-1,sc[qry].x+1);
		addq(0,0,N-1,sc[qry].x,sc[qry].y);
		//printf("%lld\n",sol);
	}
	printf("%lld\n",sol);
	return 0;
}

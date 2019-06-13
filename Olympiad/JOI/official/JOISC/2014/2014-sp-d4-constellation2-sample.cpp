#include <cstdio>
#include <cstdlib>
#include <cmath>

int N,notchecked;
int px[3002];
int py[3002];
int cl[3002];
typedef struct {
	int dx;
	int dy;
	int id;
}events;
events event[9999];

int cmp(const void *ka,const void *kb) {
	events *a=(events *)ka;
	events *b=(events *)kb;
	int kadx=a->dx;
	int kady=a->dy;
	int kbdx=b->dx;
	int kbdy=b->dy;
	while(1) {
		if(kadx>=0&&kady>=0) {
			if(kbdx>=0&&kbdy>=0) {
				long long cmpa=kady;
				cmpa*=kbdx;
				long long cmpb=kadx;
				cmpb*=kbdy;
				if(cmpa<cmpb) return -1;
				if(cmpa>cmpb) return 1;
				return 0;
			} else {
				return -1;
			}
		} else {
			if(kbdx>=0&&kbdy>=0) return 1;
		}
		int kc=kady;
		kady=-kadx;
		kadx=kc;
		kc=kbdy;
		kbdy=-kbdx;
		kbdx=kc;
	}
}
int cols[6];
int sides[3002];
int checked[3002];
long long sol=0;
void add_tris(int cola,int colb) {
	long long kadd=1;
	if(cola!=0) kadd*=cols[0];
	if(cola!=1) kadd*=cols[1];
	if(cola!=2) kadd*=cols[2];
	long long ladd=1;
	if(colb!=0) ladd*=cols[3];
	if(colb!=1) ladd*=cols[4];
	if(colb!=2) ladd*=cols[5];
	sol+=(kadd*ladd);
}
int main() {
	scanf("%d",&N);
	for(int i=0;i<N;i++) scanf("%d%d%d",&px[i],&py[i],&cl[i]);
	for(int i=0;i<N;i++) {
		int ttl=0;
		for(int j=0;j<6;j++) cols[j]=0;
		for(int j=0;j<N;j++) {
			sides[j]=0;
			checked[j]=0;
			if(i!=j) {
				event[ttl].dx=px[j]-px[i];
				event[ttl].dy=py[j]-py[i];
				event[ttl].id=j+1;
				ttl++;
				event[ttl].dx=px[i]-px[j];
				event[ttl].dy=py[i]-py[j];
				event[ttl].id=-j-1;
				ttl++;
			}
		}
		qsort(event,ttl,sizeof(events),cmp);
		notchecked=N-1;
		for(int ll=0;ll<2;ll++) {
			for(int j=0;j<ttl;j++) {
				int nw=event[j].id;
				if(nw>0) {
					nw--;
					if(sides[nw]==2) cols[cl[nw]+3]--;
					if(sides[nw]==0) notchecked--;
					sides[nw]=1;
					cols[cl[nw]]++;
					if(notchecked==0) {
						if(checked[nw]==0) {
							checked[nw]=1;
							cols[cl[nw]]--;
							add_tris(cl[i],cl[nw]);
							cols[cl[nw]]++;
						}
					}
				} else {
					nw++;
					nw=-nw;
					if(sides[nw]==1) cols[cl[nw]]--;
					if(sides[nw]==0) notchecked--;
					sides[nw]=2;
					cols[cl[nw]+3]++;
				}
			}
		}
	}
	printf("%lld\n",sol/2);
	return 0;
}

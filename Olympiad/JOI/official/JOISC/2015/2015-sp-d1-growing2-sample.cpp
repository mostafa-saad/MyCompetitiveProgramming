#include <cstdio>
#include <cstdlib>

int N;
int hs[300008];
int ps[300008];
int cs[300008];
int hvaluesall;
int hvalues[300008];
long long INF;
int cmp(const void *ka,const void *kb) {
	int a=*(int *)ka;
	int b=*(int *)kb;
	return a-b;
}
int binary_search(int vl) {
	int minv=0;
	int maxv=hvaluesall-1;
	while(minv<maxv) {
		int hf=(minv+maxv)/2;
		if(hvalues[hf]<vl) {
			minv=hf+1;
		} else {
			maxv=hf;
		}
	}
	return minv;
}
long long range_max[900008]; // segment tree
long long range_value[900008]; // segment tree
long long opt_left[300008];
long long opt_right[300008];
long long getmax(long long a,long long b) {
	if(a<b) return b;
	return a;
}
void init(void) {
	for(int i=0;i<900008;i++) {
		range_max[i]=0;
		range_value[i]=0;
	}
}
void add_range(int id,int left,int right,int range_left,int range_right,int add_value) {
	if(range_left<=left&&right<=range_right) {
		range_value[id]+=add_value;
		range_max[id]+=add_value;
		return;
	}
	if(range_left>right||left>range_right) return;
	int hf=(left+right)/2;
	add_range(id*2+1,left,hf,range_left,range_right,add_value);
	add_range(id*2+2,hf+1,right,range_left,range_right,add_value);
	range_max[id]=range_value[id]+getmax(range_max[id*2+1],range_max[id*2+2]);
}
void change_value(int id,int left,int right,int change_place,long long new_value) {
	if(change_place>right||left>change_place) return;
	if(left==right) {
		range_value[id]=new_value;
		range_max[id]=new_value;
		return;
	}
	int hf=(left+right)/2;
	change_value(id*2+1,left,hf,change_place,new_value-range_value[id]);
	change_value(id*2+2,hf+1,right,change_place,new_value-range_value[id]);
	range_max[id]=range_value[id]+getmax(range_max[id*2+1],range_max[id*2+2]);
}
long long calc_max(int id,int left,int right,int range_left,int range_right) {
	if(range_left<=left&&right<=range_right) return range_max[id];
	if(range_left>right||left>range_right) return -INF;
	int hf=(left+right)/2;
	return getmax(calc_max(id*2+1,left,hf,range_left,range_right),calc_max(id*2+2,hf+1,right,range_left,range_right))+range_value[id];
}
int main() {
	INF=1000000007;
	INF*=INF;
	scanf("%d",&N);
	for(int i=0;i<N;i++) {
		scanf("%d%d%d",&hs[i],&ps[i],&cs[i]);
		hvalues[i]=hs[i];
	}
	qsort(hvalues,N,sizeof(int),cmp);
	hvaluesall=1;
	for(int i=1;i<N;i++) {
		if(hvalues[hvaluesall-1]!=hvalues[i]) {
			hvalues[hvaluesall++]=hvalues[i];
		}
	}
	opt_left[0]=ps[0];
	int hnow=binary_search(hs[0]);
	change_value(0,0,N-1,hnow,ps[0]);
	if(hnow) add_range(0,0,N-1,0,hnow-1,-cs[0]);
	long long costsum=cs[0];
	for(int i=1;i<N;i++) {
		hnow=binary_search(hs[i]);
		opt_left[i]=ps[i]-costsum;
		opt_left[i]=getmax(opt_left[i],calc_max(0,0,N-1,0,hnow)+ps[i]);
		opt_left[i]=getmax(opt_left[i],calc_max(0,0,N-1,hnow,hnow));
		if(calc_max(0,0,N-1,hnow,hnow)<opt_left[i]) change_value(0,0,N-1,hnow,opt_left[i]);
		if(hnow) add_range(0,0,N-1,0,hnow-1,-cs[i]);
		costsum+=cs[i];
	}
	init();
	opt_right[N-1]=ps[N-1];
	hnow=binary_search(hs[N-1]);
	change_value(0,0,N-1,hnow,ps[N-1]);
	if(hnow) add_range(0,0,N-1,0,hnow-1,-cs[N-1]);
	costsum=cs[N-1];
	for(int i=N-2;i>=0;i--) {
		hnow=binary_search(hs[i]);
		opt_right[i]=ps[i]-costsum;
		opt_right[i]=getmax(opt_right[i],calc_max(0,0,N-1,0,hnow)+ps[i]);
		opt_right[i]=getmax(opt_right[i],calc_max(0,0,N-1,hnow,hnow));
		if(calc_max(0,0,N-1,hnow,hnow)<opt_right[i]) change_value(0,0,N-1,hnow,opt_right[i]);
		if(hnow) add_range(0,0,N-1,0,hnow-1,-cs[i]);
		costsum+=cs[i];
	}
	long long sol=opt_right[0];
	long long lopt=opt_left[0];
	for(int i=1;i<N;i++) {
		if(sol<lopt+opt_right[i]) sol=lopt+opt_right[i];
		if(lopt<opt_left[i]) lopt=opt_left[i];
	}
	printf("%lld\n",sol);
	return 0;
}

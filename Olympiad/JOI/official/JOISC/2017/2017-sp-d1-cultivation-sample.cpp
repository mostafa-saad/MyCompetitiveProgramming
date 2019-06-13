#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;
int R,C,N;
int rs[408];
int cs[408];
long long sol=999999999;
long long INF;
int cand_len;
int cand[3999];
int cmp(const void *ka,const void *kb) {int a=*(int *)ka;int b=*(int *)kb; return a-b;}
int uniq(int *retsu,int len) {
	qsort(retsu,len,sizeof(int),cmp);
	int nl=1;
	for(int i=1;i<len;i++) if(retsu[i]!=retsu[nl-1]) retsu[nl++]=retsu[i];
	return nl;
}
int cs_uniq_len;
int cs_uniq[3999];
vector<long long> qrs_tmg[3999];
vector<long long> qrs_L[3999];
vector<long long> qrs_R[3999];
vector<long long> qrs_C[3999];
void calc(int plc) {
	int Rnow=cand[plc];
	int filled[3999];
	long long max_noexist[3999];
	for(int i=0;i<cs_uniq_len;i++) max_noexist[i]=INF;
	for(int i=0;i<N;i++) {
		if(Rnow>=rs[i]) for(int j=0;j<cs_uniq_len;j++) if(cs_uniq[j]==cs[i]) if(max_noexist[j]>Rnow-rs[i]-1) max_noexist[j]=Rnow-rs[i]-1;
	}
	for(int i=0;i<cs_uniq_len;i++) if(max_noexist[i]<INF){filled[i]=1;}else{filled[i]=0;}
	long long cur=INF;
	//INF 時の処理
	qrs_tmg[plc].push_back(INF);
	int exist=0;
	for(int j=0;j<cs_uniq_len;j++) exist+=filled[j];
	if(exist) {
		int next=qrs_L[plc].size();
		for(int j=0;j<cs_uniq_len;j++) if(filled[j]) {qrs_L[plc].push_back(cs_uniq[j]-1);break;}
		for(int j=cs_uniq_len-1;j>=0;j--) if(filled[j]) {qrs_R[plc].push_back(C-cs_uniq[j]);break;}
		qrs_C[plc].push_back(0);
		int recent=qrs_L[plc][next];
		for(int j=0;j<cs_uniq_len;j++) if(filled[j]) {
			if(qrs_C[plc][next]<cs_uniq[j]-recent-1) qrs_C[plc][next]=cs_uniq[j]-recent-1;
			recent=cs_uniq[j];
		}
	} else {
		qrs_L[plc].push_back(INF);
		qrs_R[plc].push_back(INF);
		qrs_C[plc].push_back(INF);
	}
	//それ以外
	while(cur>=0) {
		long long nextmax=-1;
		for(int j=0;j<cs_uniq_len;j++) if(max_noexist[j]<cur&&max_noexist[j]>nextmax) nextmax=max_noexist[j];
		cur=nextmax;
		for(int j=0;j<cs_uniq_len;j++) if(max_noexist[j]==cur) filled[j]=0;
		//更新クエリ
		qrs_tmg[plc].push_back(cur);
		exist=0;
		for(int j=0;j<cs_uniq_len;j++) exist+=filled[j];
		if(exist) {
			int next=qrs_L[plc].size();
			for(int j=0;j<cs_uniq_len;j++) if(filled[j]) {qrs_L[plc].push_back(cs_uniq[j]-1);break;}
			for(int j=cs_uniq_len-1;j>=0;j--) if(filled[j]) {qrs_R[plc].push_back(C-cs_uniq[j]);break;}
			qrs_C[plc].push_back(0);
			int recent=qrs_L[plc][next];
			for(int j=0;j<cs_uniq_len;j++) if(filled[j]) {
				if(qrs_C[plc][next]<cs_uniq[j]-recent-1) qrs_C[plc][next]=cs_uniq[j]-recent-1;
				recent=cs_uniq[j];
			}
		} else {
			qrs_L[plc].push_back(INF);
			qrs_R[plc].push_back(INF);
			qrs_C[plc].push_back(INF);
		}
	}
}
typedef struct {
	long long tmg;
	long long L;
	long long R;
	long long C;
	long long from;
}evs;
evs event[999999];
int cmp2(const void *ka,const void *kb) {
	evs *a=(evs *)ka; evs *b=(evs *)kb;
	if(a->tmg<b->tmg) return 1;
	if(a->tmg>b->tmg) return -1;
	return 0;
}
int main() {
	scanf("%d%d%d",&R,&C,&N);
	for(int i=0;i<N;i++) scanf("%d%d",&rs[i],&cs[i]);
	sol*=sol;
	INF=sol;
	int cand_temp=0;
	for(int i=0;i<N;i++) {
		cs_uniq[i]=cs[i];
		cand[cand_temp++]=rs[i];
		if(rs[i]>1) cand[cand_temp++]=rs[i]-1;
		cand[cand_temp++]=rs[i]+R-1;
	}
	cs_uniq[N]=1; cs_uniq[N+1]=C;
	cs_uniq_len=uniq(cs_uniq,N+2);
	cand[cand_temp++]=1; cand[cand_temp++]=R;
	cand_len=uniq(cand,cand_temp);
	for(int i=0;i<cand_len;i++) calc(i);
	int events_len=0;
	for(int i=0;i<cand_len;i++) for(int j=0;j<qrs_tmg[i].size();j++) {
		event[events_len].tmg=qrs_tmg[i][j];
		event[events_len].L=qrs_L[i][j];
		event[events_len].R=qrs_R[i][j];
		event[events_len].from=cand[i];
		event[events_len++].C=qrs_C[i][j];
	}
	qsort(event,events_len,sizeof(evs),cmp2);
	for(int looklf=0;looklf<cand_len;looklf++) {
		if(cand[looklf]>R) break;
		long long North=cand[looklf]-1;
		int lookrg=looklf;
		while(lookrg<cand_len-1) {
			if(cand[lookrg+1]>cand[looklf]+R-1) break;
			lookrg++;
		}
		long long cur_L=0;
		long long cur_R=0;
		long long cur_C=0;
		long long recent_tmg=INF;
		for(int i=0;i<events_len;i++) {
			if(event[i].from<cand[looklf]||event[i].from>cand[lookrg]) continue;
			if(recent_tmg!=event[i].tmg) {
				if(North>event[i].tmg+1) {
					if(cur_L+cur_R>cur_C) {
						if(sol>cur_L+cur_R+North) sol=cur_L+cur_R+North;
					} else {
						if(sol>cur_C+North) sol=cur_C+North;
					}
				} else {
					if(cur_L+cur_R>cur_C) {
						if(sol>cur_L+cur_R+event[i].tmg+1) sol=cur_L+cur_R+event[i].tmg+1;
					} else {
						if(sol>cur_C+event[i].tmg+1) sol=cur_C+event[i].tmg+1;
					}
				}
			}
			recent_tmg=event[i].tmg;
			if(cur_L<event[i].L) cur_L=event[i].L;
			if(cur_R<event[i].R) cur_R=event[i].R;
			if(cur_C<event[i].C) cur_C=event[i].C;
		}
		//S=0
		if(cur_L+cur_R>cur_C) {
			if(sol>cur_L+cur_R+North) sol=cur_L+cur_R+North;
		} else {
			if(sol>cur_C+North) sol=cur_C+North;
		}
	}
	printf("%lld\n",sol);
	return 0;
}

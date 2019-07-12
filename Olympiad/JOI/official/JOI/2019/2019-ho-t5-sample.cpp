#include <bits/stdc++.h>
#include <type_traits>
using namespace std;

using ll=int64_t;
#define int ll

#define FOR(i,a,b) for(int i=int(a);i<int(b);i++)
#define REP(i,b) FOR(i,0,b)
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define ALL(x) x.begin(),x.end()
auto& errStream=cerr;
#ifdef LOCAL
#define cerr (cerr<<"-- line "<<__LINE__<<" -- ")
#else
class CerrDummy{}cerrDummy;
template<class T>
CerrDummy& operator<<(CerrDummy&cd,const T&){
	return cd;
}
using charTDummy=char;
using traitsDummy=char_traits<charTDummy>;
CerrDummy& operator<<(CerrDummy&cd,basic_ostream<charTDummy,traitsDummy>&(basic_ostream<charTDummy,traitsDummy>&)){
	return cd;
}
#define cerr cerrDummy
#endif
#define REACH cerr<<"reached"<<endl
#define DMP(x) cerr<<#x<<":"<<x<<endl
#define ZERO(x) memset(x,0,sizeof(x))
#define ONE(x) memset(x,-1,sizeof(x))

using pi=pair<int,int>;
using vi=vector<int>;
using ld=long double;

template<class T,class U>
ostream& operator<<(ostream& os,const pair<T,U>& p){
	os<<"("<<p.first<<","<<p.second<<")";
	return os;
}

template<class T>
ostream& operator <<(ostream& os,const vector<T>& v){
	os<<"{";
	REP(i,(int)v.size()){
		if(i)os<<",";
		os<<v[i];
	}
	os<<"}";
	return os;
}

ll read(){
	ll i;
	scanf("%"  SCNd64,&i);
	return i;
}

void printSpace(){
	printf(" ");
}

void printEoln(){
	printf("\n");
}

void print(ll x,int suc=1){
	printf("%" PRId64,x);
	if(suc==1)
		printEoln();
	if(suc==2)
		printSpace();
}

string readString(){
	static char buf[3341000];
	scanf("%s",buf);
	return string(buf);
}

char* readCharArray(){
	static char buf[3341000];
	static int bufUsed=0;
	char* ret=buf+bufUsed;
	scanf("%s",ret);
	bufUsed+=strlen(ret)+1;
	return ret;
}

template<class T,class U>
void chmax(T& a,U b){
	if(a<b)
		a=b;
}

template<class T,class U>
void chmin(T& a,U b){
	if(b<a)
		a=b;
}

template<class T>
T Sq(const T& t){
	return t*t;
}

#define CAPITAL
void Yes(bool ex=true){
	#ifdef CAPITAL
	cout<<"YES"<<endl;
	#else
	cout<<"Yes"<<endl;
	#endif
	if(ex)exit(0);
}
void No(bool ex=true){
	#ifdef CAPITAL
	cout<<"NO"<<endl;
	#else
	cout<<"No"<<endl;
	#endif
	if(ex)exit(0);
}

const ll infLL=LLONG_MAX/3;

#ifdef int
const int inf=infLL;
#else
const int inf=INT_MAX/2-100;
#endif

const int Nmax=200010;
vi tr[Nmax];
int ans[Nmax];
int col[Nmax],cnt[Nmax],curAns,stBuf[Nmax],stS;
void AddCol(int c){
	if(cnt[c]==0)
		curAns++;
	cnt[c]++;
}
void DelCol(int c){
	cnt[c]--;
	if(cnt[c]==0)
		curAns--;
}
void Push(int v){
	stBuf[stS++]=v;
	AddCol(col[v]);
}
bool Empty(){
	return stS==0;
}
int Last(){
	return stBuf[stS-1];
}
void Pop(){
	DelCol(col[Last()]);
	stS--;
}

void dfs1(int v,int p,int d,vi&dist){
	dist[v]=d;
	for(auto to:tr[v])
		if(to!=p)
			dfs1(to,v,d+1,dist);
}

int dep[Nmax];
int dfs2(int v,int p){
	int res=0;
	for(auto to:tr[v])
		if(to!=p)
			chmax(res,dfs2(to,v));
	return dep[v]=res+1;
}

void dfs3(int v,int p,const vi&dist){
	vector<pi> ch;
	for(auto to:tr[v])
		if(to!=p)
			ch.EB(dep[to],to);
	if(!ch.empty()){
		swap(ch[0],*max_element(ALL(ch)));
		int len=ch.size()>1?max_element(ch.begin()+1,ch.end())->first:0;
		for(auto c:ch){
			int to=c.second;
			while(!Empty()&&dist[Last()]>=dist[v]-len)
				Pop();
			Push(v);
			dfs3(to,v,dist);
			if(!Empty()&&Last()==v)
				Pop();
			chmax(len,c.first);
		}
		while(!Empty()&&dist[Last()]>=dist[v]-len)
			Pop();
	}
	chmax(ans[v],curAns);
}

void Solve(int root,const vi&dist){
	assert(Empty());
	dfs2(root,-1);
	dfs3(root,-1,dist);
}

signed main(){
	int n=read(),k=read();
	REP(_,n-1){
		int a=read()-1,b=read()-1;
		tr[a].PB(b);
		tr[b].PB(a);
	}
	REP(i,n)
		col[i]=read()-1;
	
	vi dist(n);
	dfs1(0,-1,0,dist);
	int root=max_element(ALL(dist))-dist.begin();
	dfs1(root,-1,0,dist);
	Solve(root,dist);
	
	root=max_element(ALL(dist))-dist.begin();
	dfs1(root,-1,0,dist);
	Solve(root,dist);
	
	REP(i,n)
		print(ans[i]);
}

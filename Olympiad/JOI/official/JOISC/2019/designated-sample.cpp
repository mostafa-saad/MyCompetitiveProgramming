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

template<int i,class T>
void print_tuple(ostream&,const T&){
}

template<int i,class T,class H,class ...Args>
void print_tuple(ostream&os,const T&t){
	if(i)os<<",";
	os<<get<i>(t);
	print_tuple<i+1,T,Args...>(os,t);
}

template<class ...Args>
ostream& operator<<(ostream&os,const tuple<Args...>&t){
	os<<"(";
	print_tuple<0,tuple<Args...>,Args...>(os,t);
	return os<<")";
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

template<class T>
void print(const vector<T>&v){
	REP(i,v.size())
		print(v[i],i==int(v.size())-1?1:2);
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

constexpr ll TEN(int n){
	return n==0?1:TEN(n-1)*10;
}

template<class T>
vector<T> Uniqued(const vector<T>&vv){
	auto v(vv);
	sort(ALL(v));
	v.erase(unique(ALL(v)),v.end());
	return v;
}
template<class T>
void MakeUniqued(vector<T>&v){
	sort(ALL(v));
	v.erase(unique(ALL(v)),v.end());
}

const int Nmax=200010;
int cost[Nmax*2];
vector<pi> tr[Nmax];
int n,ans[Nmax],inCost[Nmax];

int dfs1(int v,int p){
	int res=0;
	for(auto e:tr[v])if(e.first!=p){
		res+=cost[e.second^1];
		res+=dfs1(e.first,v);
	}
	return res;
}

void dfs2(int v,int p,int cur){
	inCost[v]=cur;
	for(auto e:tr[v])if(e.first!=p){
		dfs2(e.first,v,cur+cost[e.second]-cost[e.second^1]);
	}
}

void Solve1(){
	inCost[0]=dfs1(0,-1);
	dfs2(0,-1,inCost[0]);
	ans[1]=*max_element(inCost,inCost+n);
}

pi dfs3(int v,int p,tuple<int,int,int>&dst){
	pi res(inCost[v],v);
	for(auto e:tr[v])if(e.first!=p){
		pi w=dfs3(e.first,v,dst);
		w.first+=cost[e.second]+cost[e.second^1];
		chmax(dst,make_tuple(res.first+w.first,res.second,w.second));
		chmax(res,w);
	}
	return res;
}

pi Solve2(){
	tuple<int,int,int> res(-1,-1,-1);
	dfs3(0,-1,res);
	ans[2]=get<0>(res)/2;
	return pi(get<1>(res),get<2>(res));
}

bool used[Nmax];
int par[Nmax];
pi maxDep[Nmax];
vi ch[Nmax];
pi dfs4(int v,int p,int pCost){
	par[v]=p;
	pi res(0,v);
	for(auto e:tr[v])if(e.first!=p){
		ch[v].PB(e.first);
		pi w=dfs4(e.first,v,cost[e.second]);
		chmax(res,w);
	}
	res.first+=pCost;
	maxDep[v]=res;
	return res;
}
void SolveAll(int root){
	dfs4(root,-1,0);
	
	priority_queue<pi> pq;
	const auto Mark=[&](int v){
		used[v]=true;
		for(auto c:ch[v])if(!used[c])
			pq.push(maxDep[c]);
	};
	Mark(root);
	
	int cnt=2,cur=inCost[root];
	while(!pq.empty()){
		pi w=pq.top();pq.pop();
		int d=w.first,x=w.second;
		ans[cnt++]=(cur+=d);
		while(!used[x]){
			Mark(x);
			x=par[x];
		}
	}
	while(cnt<=n){
		ans[cnt++]=cur;
	}
}

signed main(){
	n=read();
	assert(n<=Nmax);
	int sum=0;
	REP(i,n-1){
		int a=read()-1,b=read()-1,c=read(),d=read();
		tr[a].EB(b,i*2);
		cost[i*2]=c;
		tr[b].EB(a,i*2+1);
		cost[i*2+1]=d;
		sum+=c+d;
	}
	Solve1();
	pi w=Solve2();
	SolveAll(w.first);
	int q=read();
	REP(i,q){
		int e=read();
		print(sum-ans[e]);
	}
}

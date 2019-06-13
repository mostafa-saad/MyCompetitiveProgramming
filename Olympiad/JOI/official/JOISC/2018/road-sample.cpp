#define DEB
#include<bits/stdc++.h>
#define REP(i,m) for(int i=0;i<(m);++i)
#define REPN(i,m,in) for(int i=(in);i<(m);++i)
#define ALL(t) (t).begin(),(t).end()
#define CLR(a) memset((a),0,sizeof(a))
#define pb push_back
#define mp make_pair
#define fr first
#define sc second

using namespace std;


#ifdef DEB
#define dump(x)  cerr << #x << " = " << (x) << endl
#define prl cerr<<"called:"<< __LINE__<<endl
template<class T> void 
debug(T a,T b){ for(;a!=b;++a) cerr<<*a<<' ';cerr<<endl;}
#else
#define dump(x) ;
#define prl ;
template<class T> void debug(T a,T b){ ;}
#endif

template<class T> void chmin(T& a,const T& b) { if(a>b) a=b; }
template<class T> void chmax(T& a,const T& b) { if(a<b) a=b; }

typedef long long int lint;
typedef pair<int,int> pi;

namespace std{
  template<class S,class T>
  ostream &operator <<(ostream& out,const pair<S,T>& a){
    out<<'('<<a.fr<<','<<a.sc<<')';
    return out;
  }
}

const int INF=5e8;

int n,K;
const int MAX_N=1005;
typedef vector<int> vi;
typedef vector<pi> vp;
vector<int> g[MAX_N];

vector<int> G[MAX_N];

int dall(int i){
  int res=0;
  int d[MAX_N];
  memset(d,-1,sizeof(d));
  queue<int> q;q.push(i);
  d[i]=0;
  while(!q.empty()){
    int v=q.front();q.pop();
    for(auto to:G[v]) if(d[to]==-1){
      d[to]=d[v]+1;
      q.push(to);
    }
  }
  REP(j,n) res+=d[j];
  return res;
}
int eval(const vp& add){
  REP(j,n) G[j]=g[j];
  for(auto e:add) G[e.fr].pb(e.sc),G[e.sc].pb(e.fr);

  int res=0;
  REP(i,n){
    res+=dall(i);
  }
  return res/2;
}

vp ans;
int ansScore=INF,ansScore2=INF;

int eval2(const vp& add,int v){
  REP(i,n) G[i]=g[i];
  for(auto e:add) G[e.fr].pb(e.sc),G[e.sc].pb(e.fr);
  return dall(v);
}
void renew(const vp& add,int v){
  int Y=eval(add);
  if(ansScore>Y){
    ansScore=Y;
    ans=add;
  }
}
uint32_t xrand(void) { 
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123; 
  uint32_t t;
 
  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)); 
}
double R(double a,double b){
  return xrand()*1.0/(1ll<<32)*(b-a)+a;
}
int main(){
  int W;
  cin>>n>>K>>W;
  REP(i,n-1){
    int a,b;cin>>a>>b;--a;--b;
    g[a].pb(b);
    g[b].pb(a);
  }
  REP(i,n) sort(ALL(g[i]));

  vector<pair<double,pair<pair<int,double>,pair<vi,vi> > > > task;


  auto MP=[&](vi& X,int v){
    vp res;
    for(auto e:X) res.pb({e,v});
    return res;
  };
  REP(i,n){
    vi cands;
    REP(j,n) if(i!=j && !binary_search(ALL(g[i]),j)) cands.pb(j);

    double score[MAX_N];

    const int M=100;
    REP(t,M){
      double mxi=R(0,5);
      for(auto e:cands) score[e]=g[e].size()+R(0,mxi);
      sort(ALL(cands),[&](int a,int b){
        return score[a]>score[b];
      });
      vi X,Y;
      REP(j,cands.size()){
        if(j<K) X.pb(cands[j]);
        else Y.pb(cands[j]);
      }
      task.pb({eval2(MP(X,i),i),{{i,mxi},{X,Y}}});
    }
  }
  sort(ALL(task));
  const int M2=10;
  if(task.size()>M2) task.resize(M2);
  for(auto e:task){
    int i=e.sc.fr.fr;
    double mxi=e.sc.fr.sc;
    vi X=e.sc.sc.fr,Y=e.sc.sc.sc;

    {
      auto eval4=[&](){
        vp add;
        for(auto e:X) add.pb({e,i});
        return eval(add);
      };
      auto eval3=[&](){
        vp add;
        for(auto e:X) add.pb({e,i});
        return eval2(add,i);
      };

      int cnt=0;
      while(1){
        int cur=eval3();

        int best=cur,jj,kk;
        REP(j,X.size()) REP(k,Y.size()){
          swap(X[j],Y[k]);
          int nxt=eval3();
          if(nxt<best){
            jj=j;kk=k;
            best=nxt;
          }
          swap(X[j],Y[k]);
        }
        renew(MP(X,i),i);

        if(best<cur){
          swap(X[jj],Y[kk]);
          ++cnt;
        }else{
          break;
        }
      }
      vp add;
      REP(j,X.size()) add.pb({X[j],i});

      renew(add,i);
    }
  }
  for(auto e:ans) printf("%d %d\n",e.fr+1,e.sc+1);
  return 0;
}
